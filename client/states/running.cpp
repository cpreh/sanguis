#include "running.hpp"
#include "menu.hpp"
#include "gameover.hpp"
#include "../perk_cast.hpp"
#include "../message_event.hpp"
#include "../menu_event.hpp"
#include "../log.hpp"
#include "../invalid_id.hpp"
#include "../entity_type.hpp"
#include "../control/logic.hpp"
#include "../control/input_handler.hpp"
#include "../cursor/object.hpp"
#include "../messages/add.hpp"
#include "../messages/visible.hpp"
#include "../draw2d/screen_to_virtual.hpp" // FIXME
#include "../draw2d/scene/object.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/assign_id.hpp"
#include "../../messages/remove_id.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/available_perks.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../messages/move.hpp"
#include "../../messages/create.hpp"
#include "../../load/context.hpp"
#include "../../tick_event.hpp"
#include "../../cast_enum.hpp"
#include <sge/audio/pool.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/systems/instance.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/assert.hpp>
#include <boost/mpl/vector/vector10.hpp>
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
		context<machine>().console_wrapper().object(),
		context<machine>().resources().resources().sounds()
	),
	drawer(
		new draw2d::scene::object(
			context<machine>().resources(),
			context<machine>().renderer(),
			context<machine>().font(),
			context<machine>().cursor()
		)
	),
	logic_(
		new control::logic(
			std::tr1::bind(
				&running::send_message,
				this,
				std::tr1::placeholders::_1
			),
			drawer->control_environment(),
			context<machine>().console_wrapper().object().object()
		)
	),
	input(
		new control::input_handler(
			std::tr1::bind(
				&control::logic::handle_player_action,
				logic_.get(),
				std::tr1::placeholders::_1
			)
		)
	),
	input_connection(
		context<machine>().console_wrapper().register_callback(
			std::tr1::bind(
				&control::input_handler::input_callback,
				input.get(),
				std::tr1::placeholders::_1
			)
		)
	),
	perk_chooser_(
		context<machine>().sys(),
		std::tr1::bind(
			&running::send_perk_choose,
			this,
			std::tr1::placeholders::_1
		),
		context<machine>().cursor()
	),
	cursor_id(
		drawer->client_message(
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
	drawer->client_message(
		client::messages::add(
			client::entity_type::background
		)
	);
}

sanguis::client::states::running::~running()
{}

void 
sanguis::client::states::running::draw(
	tick_event const &t
)
{
	drawer->draw(t.delta());

	perk_chooser_.process();
}

void 
sanguis::client::states::running::process(
	tick_event const &t
)
{
	context<machine>().dispatch();

	context<machine>().resources().update(
		t.delta()
	);

	context<machine>().sound_pool().update();

	music_.process();
}

void 
sanguis::client::states::running::pause(
	bool const b
)
{
	logic_->pause(b);

	drawer->pause(b);
}

boost::statechart::result
sanguis::client::states::running::react(
	message_event const &m
)
{
	static sanguis::messages::call::object<
		boost::mpl::vector7<
			sanguis::messages::assign_id,
			sanguis::messages::remove_id,
			sanguis::messages::disconnect,
			sanguis::messages::give_weapon,
			sanguis::messages::highscore,
			sanguis::messages::available_perks,
			sanguis::messages::level_up
		>,
		running
	> dispatcher;

	return dispatcher(
		*m.message(),
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
	sanguis::messages::assign_id const &m
)
{
	drawer->player_id(
		m.get<sanguis::messages::roles::entity_id>()
	);

	input->active(
		true
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::remove_id const &
)
{
	drawer->player_id(
		invalid_id
	);

	input->active(
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
	sanguis::messages::give_weapon const &m
)
{
	logic_->give_player_weapon(
		SANGUIS_CAST_ENUM(
			weapon_type,
			m.get<sanguis::messages::roles::weapon>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::highscore const &m
)
{
	FCPPT_LOG_DEBUG(
		sanguis::client::log(),
		fcppt::log::_ 
			<< FCPPT_TEXT("got highscore message, score was: ")
			<< m.get<sanguis::messages::roles::highscore>()
	);

	BOOST_FOREACH(
		sanguis::messages::types::string const &s,
		m.get<sanguis::messages::string_vector>()
	)
		context<machine>().gameover_names().push_back(
			fcppt::utf8::convert(
				s
			)
		);
	
	context<machine>().gameover_score(
		static_cast<highscore::score_type>(
			m.get<sanguis::messages::roles::highscore>()
		));
	
	return transit<gameover>();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::available_perks const &m
)
{
	perk_chooser_.perks(
		perk_cast(
			m.get<sanguis::messages::perk_list>()
		)
	);

	return forward_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::level_up const &m
)
{
	perk_chooser_.level_up(
		static_cast<level_type>(
			m.get<sanguis::messages::level_type>()
		)
	);

	drawer->process_message(
		*sanguis::messages::create(
			m
		)
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
	sanguis::messages::base const &m
)
{
	drawer->process_message(m);

	return discard_event();
}

void
sanguis::client::states::running::send_message(
	sanguis::messages::auto_ptr m
)
{
	context<machine>().send(
		m
	);
}

void
sanguis::client::states::running::send_perk_choose(
	perk_type::type const m
)
{
	send_message(
		sanguis::messages::create(
			sanguis::messages::player_choose_perk(
				m
			)
		)
	);
}

void
sanguis::client::states::running::cursor_pos(
	draw2d::sprite::point const &pos // FIXME
)
{
	drawer->process_message(
		*sanguis::messages::create(
			sanguis::messages::move(
				cursor_id,
				draw2d::screen_to_virtual( // FIXME
					context<machine>().renderer()->screen_size(),
					pos
				)
			)
		)
	);
}

void
sanguis::client::states::running::cursor_show(
	bool const show
)
{
	drawer->client_message(
		client::messages::visible(
			cursor_id,
			!show
		)
	);
}
