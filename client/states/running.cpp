#include "running.hpp"
#include "menu.hpp"
#include "gameover.hpp"
#include "../perk_cast.hpp"
#include "../next_id.hpp"
#include "../message_event.hpp"
#include "../menu_event.hpp"
#include "../log.hpp"
#include "../../client_entity_type.hpp"
#include "../../client_messages/add.hpp"
#include "../../client_messages/visible.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/assign_id.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/available_perks.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../messages/move.hpp"
#include "../../messages/remove.hpp"
#include "../../messages/create.hpp"
#include "../../draw/coord_transform.hpp"
#include "../../draw/scene.hpp"
#include "../../load/context.hpp"
#include "../../tick_event.hpp"
#include "../cursor/object.hpp"
#include <sge/log/headers.hpp>
#include <sge/renderer/device.hpp>
#include <sge/audio/pool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/systems/instance.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/assert.hpp>
#include <sge/utf8/convert.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/foreach.hpp>
#include <tr1/functional>

namespace
{

sanguis::entity_id const
	cursor_id(sanguis::client::next_id()),
	background_id(sanguis::client::next_id()),
	healthbar_id(sanguis::client::next_id());

}

sanguis::client::states::running::running(
	my_context ctx)
:
	my_base(ctx), 
	renderer_state_(
		context<machine>().renderer(),
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = false)
			(sge::renderer::state::bool_::clear_zbuffer = false)
	),
	music_(
		context<machine>().console_wrapper().con,
		context<machine>().resources().resources().sounds()
	),
	drawer(
		new draw::scene(
			context<machine>().resources(),
			context<machine>().renderer(),
			context<machine>().font()
		)
	),
	logic_(
		std::tr1::bind(
			&running::send_message,
			this,
			std::tr1::placeholders::_1
		),
		context<machine>().renderer(),
		context<machine>().cursor(),
		context<machine>().console_wrapper().con.object()
	),
	input(
		std::tr1::bind(
			&logic::handle_player_action,
			&logic_,
			std::tr1::placeholders::_1
		)
	),
	input_connection(
		context<machine>().console_wrapper().register_callback(
			std::tr1::bind(
				&input_handler::input_callback,
				&input,
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
		client_messages::add(
			::cursor_id,
			client_entity_type::cursor
		)
	);

	drawer->client_message(
		client_messages::add(
			::background_id,
			client_entity_type::background
		)
	);
}

sanguis::client::states::running::~running()
{}

void 
sanguis::client::states::running::draw(
	tick_event const &t)
{
	drawer->draw(t.delta());
	perk_chooser_.process();
}

void 
sanguis::client::states::running::process(
	tick_event const &t)
{
	context<machine>().dispatch();
	context<machine>().resources().update(
		t.delta());
	context<machine>().sound_pool().update();
	music_.process();
}

void 
sanguis::client::states::running::pause(
	bool const b)
{
	logic_.pause(b);
	drawer->pause(b);
}

boost::statechart::result
sanguis::client::states::running::react(
	message_event const &m
)
{
	static messages::call::object<
		boost::mpl::vector8<
			messages::assign_id,
			messages::disconnect,
			messages::give_weapon,
			messages::highscore,
			messages::move,
			messages::remove,
			messages::available_perks,
			messages::level_up
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
	messages::assign_id const &m)
{
	logic_.player_id(
		m.get<messages::roles::entity_id>()
	);
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::disconnect const &)
{
	return transit<menu>();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::give_weapon const &m)
{
	logic_.give_weapon(
			m);
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::move const &m)
{
	logic_.move(m);
	(*drawer)(m);
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::remove const &m)
{
	logic_.remove(
		m.get<messages::roles::entity_id>()
	);
	(*drawer)(m);
	// TODO: check the logic if we died
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::highscore const &m)
{
	SGE_LOG_DEBUG(
		sanguis::client::log(),
		sge::log::_ 
			<< FCPPT_TEXT("got highscore message, score was: ")
			<< m.get<messages::roles::highscore>()
	);

	BOOST_FOREACH(
		messages::types::string const &s,
		m.get<messages::string_vector>()
	)
		context<machine>().gameover_names().push_back(
			sge::utf8::convert(
				s
			)
		);
	
	context<machine>().gameover_score(
		static_cast<highscore::score_type>(
			m.get<messages::roles::highscore>()
		));
	
	return transit<gameover>();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::available_perks const &m)
{
	perk_chooser_.perks(
		perk_cast(
			m.get<messages::perk_list>()
		)
	);

	return forward_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::level_up const &m)
{
	perk_chooser_.level_up(
		static_cast<level_type>(
			m.get<messages::level_type>()
		)
	);

	(*drawer)(m);

	return discard_event();
}

sanguis::entity_id
sanguis::client::states::running::player_id() const
{
	return logic_.player_id();
}

sanguis::client::perk_chooser &
sanguis::client::states::running::perk_chooser()
{
	return perk_chooser_;
}

boost::statechart::result
sanguis::client::states::running::handle_default_msg(
	messages::base const &m)
{
	drawer->process_message(m);
	return discard_event();
}

void sanguis::client::states::running::send_message(
	messages::auto_ptr m)
{
	context<machine>().send(
		m);
}

void sanguis::client::states::running::send_perk_choose(
	perk_type::type const m)
{
	send_message(
		messages::create(
			messages::player_choose_perk(
				player_id(),
				m
			)
		)
	);
}

void
sanguis::client::states::running::cursor_pos(
	draw::sprite::point const &pos
)
{
	(*drawer)(
		messages::move(
			cursor_id,
			draw::screen_to_virtual(
				context<machine>().renderer()->screen_size(),
				pos
			)
		)
	);

}

void sanguis::client::states::running::cursor_show(
	bool const show)
{
	drawer->client_message(
		client_messages::visible(
			cursor_id,
			!show
		)
	);
}
