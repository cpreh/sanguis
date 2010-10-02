#include "running.hpp"
#include "menu.hpp"
#include "gameover.hpp"
#include "../perk_cast.hpp"
#include "../log.hpp"
#include "../invalid_id.hpp"
#include "../entity_type.hpp"
#include "../control/logic.hpp"
#include "../control/input_handler.hpp"
#include "../cursor/object.hpp"
#include "../events/menu.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../messages/add.hpp"
#include "../messages/visible.hpp"
#include "../draw2d/screen_to_virtual.hpp" // FIXME
#include "../draw2d/scene/object.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../messages/move.hpp"
#include "../../messages/create.hpp"
#include "../../load/context.hpp"
#include "../../cast_enum.hpp"
#include <sge/audio/pool.hpp>
#include <sge/audio/player.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/input/action.hpp>
#include <sge/input/system.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/assert.hpp>
#include <boost/mpl/vector/vector20.hpp>
#include <boost/foreach.hpp>

sanguis::client::states::running::running(
	my_context ctx
)
:
	my_base(ctx), 
	renderer_state_(
		context<machine>().renderer(),
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = false)
			(sge::renderer::state::bool_::clear_zbuffer = false)
	),
	music_(
		context<machine>().console().gfx().object(),
		context<machine>().resources().resources().sounds()
	),
	daytime_settings_(
		context<machine>().console().gfx().object()
	),
	drawer_(
		new draw2d::scene::object(
			context<machine>().resources(),
			context<machine>().renderer(),
			context<machine>().font_metrics(),
			context<machine>().font_drawer(),
			context<machine>().audio_player()->listener(),
			context<machine>().cursor(),
			daytime_settings_.current_time()
		)
	),
	logic_(
		new control::logic(
			std::tr1::bind(
				&running::send_message,
				this,
				std::tr1::placeholders::_1
			),
			std::tr1::bind(
				&running::menu_event,
				this,
				std::tr1::placeholders::_1
			),
			drawer_->control_environment(),
			context<machine>().console().gfx().object()
		)
	),
	perk_chooser_(
		context<machine>().renderer(),
		context<machine>().input_system(),
		context<machine>().image_loader(),
		context<machine>().font_metrics(),
		std::tr1::bind(
			&running::send_perk_choose,
			this,
			std::tr1::placeholders::_1
		),
		context<machine>().cursor()
	),
	cursor_id_(
		drawer_->client_message(
			client::messages::add(
				client::entity_type::cursor
			)
		)
	),
	cursor_pos_conn_(
		context<machine>().cursor()->register_pos_callback(
			std::tr1::bind(
				&running::cursor_pos,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	cursor_show_conn_(
		context<machine>().cursor()->register_visible_callback(
			std::tr1::bind(
				&running::cursor_show,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
	drawer_->client_message(
		client::messages::add(
			client::entity_type::background
		)
	);
}

sanguis::client::states::running::~running()
{}

boost::statechart::result
sanguis::client::states::running::react(
	events::tick const &_event
)
{
	drawer_->draw(
		_event.delta()
	);

	perk_chooser_.process();

	drawer_->set_time(
		daytime_settings_.current_time()
	);

	context<machine>().dispatch();

	context<machine>().resources().update(
		_event.delta()
	);

	context<machine>().sound_pool().update();

	music_.process();

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::react(
	events::message const &_event
)
{
	static sanguis::messages::call::object<
		boost::mpl::vector11<
			sanguis::messages::add_own_player,
			sanguis::messages::remove_id,
			sanguis::messages::disconnect,
			sanguis::messages::give_weapon,
			sanguis::messages::highscore,
			sanguis::messages::available_perks,
			sanguis::messages::level_up,
			sanguis::messages::console_print,
			sanguis::messages::add_console_command,
			sanguis::messages::pause,
			sanguis::messages::unpause
		>,
		running
	> dispatcher;

	return
		dispatcher(
			*_event.value(),
			*this,
			std::tr1::bind(
				&running::handle_default_msg,
				this,
				std::tr1::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::add_own_player const &_message
)
{
	// TODO: is this still needed?
	{
		sanguis::messages::auto_ptr wrapped_msg(
			sanguis::messages::create(
				_message
			)
		);

		drawer_->process_message(
			*wrapped_msg
		);
	}

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::remove_id const &
)
{
	player_input_->active(
		false
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::disconnect const &
)
{
	return transit<menu>();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::give_weapon const &_message
)
{
	logic_->give_player_weapon(
		SANGUIS_CAST_ENUM(
			weapon_type,
			_message.get<sanguis::messages::roles::weapon>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::highscore const &_message
)
{
	FCPPT_LOG_DEBUG(
		sanguis::client::log(),
		fcppt::log::_ 
			<< FCPPT_TEXT("got highscore message, score was: ")
			<< _message.get<sanguis::messages::roles::highscore>()
	);

	BOOST_FOREACH(
		sanguis::messages::types::string const &entry,
		_message.get<sanguis::messages::string_vector>()
	)
		context<machine>().gameover_names().push_back(
			fcppt::utf8::convert(
				entry	
			)
		);
	
	context<machine>().gameover_score(
		static_cast<highscore::score_type>(
			_message.get<sanguis::messages::roles::highscore>()
		)
	);
	
	return transit<gameover>();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::available_perks const &_message
)
{
	perk_chooser_.perks(
		perk_cast(
			_message.get<sanguis::messages::perk_list>()
		)
	);

	return forward_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::level_up const &_message
)
{
	perk_chooser_.level_up(
		static_cast<level_type>(
			_message.get<sanguis::messages::level_type>()
		)
	);

	drawer_->process_message(
		*sanguis::messages::create(
			_message
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::console_print const &_message
)
{
	context<machine>().console().gfx().object().emit_message(
		fcppt::utf8::convert(
			_message.get<
				sanguis::messages::string
			>()
		)
	);

	return discard_event();	
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::add_console_command const &_message
)
{
	fcppt::string const name(
		fcppt::utf8::convert(
			_message.get<
				sanguis::messages::roles::command_name
			>()
		)
	);

	FCPPT_LOG_DEBUG(
		sanguis::client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Got a new console command: ")
			<< name
	);

	context<machine>().console().register_server_command(
		name,
		fcppt::utf8::convert(
			_message.get<
				sanguis::messages::roles::command_description
			>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::pause const &
)
{
	drawer_->pause(
		true
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::unpause const &
)
{
	drawer_->pause(
		false
	);

	return discard_event();
}

sanguis::client::perk_chooser &
sanguis::client::states::running::perk_chooser()
{
	return perk_chooser_;
}

boost::statechart::result
sanguis::client::states::running::handle_default_msg(
	sanguis::messages::base const &_message
)
{
	drawer_->process_message(
		_message
	);

	return discard_event();
}

void
sanguis::client::states::running::send_message(
	sanguis::messages::auto_ptr _message
)
{
	context<machine>().send(
		_message
	);
}

void
sanguis::client::states::running::menu_event(
	control::menu_action::type const _type
)
{
	post_event(
		events::menu(
			_type
		)
	);
}

void
sanguis::client::states::running::send_perk_choose(
	perk_type::type const _perk_type
)
{
	send_message(
		sanguis::messages::create(
			sanguis::messages::player_choose_perk(
				_perk_type
			)
		)
	);
}

void
sanguis::client::states::running::cursor_pos(
	draw2d::sprite::point const &_pos // FIXME
)
{
	drawer_->process_message(
		*sanguis::messages::create(
			sanguis::messages::move(
				cursor_id_,
				draw2d::screen_to_virtual( // FIXME
					context<machine>().renderer()->screen_size(),
					_pos
				)
			)
		)
	);
}

void
sanguis::client::states::running::cursor_show(
	bool const _show
)
{
	drawer_->client_message(
		client::messages::visible(
			cursor_id_,
			!_show
		)
	);
}

void
sanguis::client::states::running::on_escape()
{
	post_event(
		events::menu()
	);
}
