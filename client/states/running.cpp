#include "running.hpp"
#include "menu.hpp"
#include "gameover.hpp"
#include "../perk_cast.hpp"
#include "../next_id.hpp"
#include "../../client_entity_type.hpp"
#include "../../client_messages/add.hpp"
#include "../../client_messages/visible.hpp"
#include "../../messages/assign_id.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/available_perks.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../messages/move.hpp"
#include "../../messages/remove.hpp"
#include "../../messages/unwrap.hpp"
#include "../../messages/create.hpp"
#include "../../draw/coord_transform.hpp"
#include "../../draw/scene.hpp"
#include "../../load/context.hpp"
#include "../log.hpp"
#include <sge/renderer/device.hpp>
#include <sge/audio/pool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/systems/instance.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/assert.hpp>
#include <sge/utf8/convert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

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
			(sge::renderer::state::bool_::clear_zbuffer = false)),
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
		boost::bind(
			&running::send_message,
			this,
			_1),
		context<machine>().sys().image_loader(),
		context<machine>().renderer(),
		boost::bind(
			&running::cursor_pos,
			this,
			_1
		),
		boost::bind(
			&running::cursor_show,
			this,
			_1
		)
	),
	input(
		boost::bind(
			&logic::handle_player_action,
			&logic_,
			_1
		)
	),
	input_connection(
		context<machine>().console_wrapper().register_callback(
			boost::bind(
				&input_handler::input_callback,
				&input,
				_1
			)
		)
	),
	perk_chooser_(
		context<machine>().sys(),
		boost::bind(
			&running::send_perk_choose,
			this,
			_1),
		logic_.cursor()
	),
	gameover_names_(),
	gameover_score_()
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
	tick_event const &)
{
	context<machine>().dispatch();
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
	message_event const &m)
{
	return messages::unwrap<
		boost::mpl::vector<
			messages::assign_id,
			messages::disconnect,
			messages::give_weapon,
			messages::highscore,
			messages::move,
			messages::remove,
			messages::available_perks,
			messages::level_up
		>,
		boost::statechart::result
	>(
		*this,
		*m.message(),
		boost::bind(
			&running::handle_default_msg,
			this,
			_1
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
		sge::log::_1 
			<< SGE_TEXT("got highscore message, score was: ")
			<< m.get<messages::roles::highscore>()
	);

	BOOST_FOREACH(
		messages::types::string const &s,
		m.get<messages::string_vector>()
	)
		gameover_names_.push_back(
			sge::utf8::convert(
				s
			)
		);
	
	gameover_score_ = 
		static_cast<highscore::score_type>(
			m.get<messages::roles::highscore>()
		);
	
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

sanguis::client::cursor_ptr
sanguis::client::states::running::cursor()
{
	return logic_.cursor();
}

sanguis::client::highscore::name_container const &
sanguis::client::states::running::gameover_names()
{
	return gameover_names_;
}

sanguis::client::highscore::score_type
sanguis::client::states::running::gameover_score()
{
	return gameover_score_;
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

void sanguis::client::states::running::cursor_pos(
	sge::sprite::point const &pos)
{
	(*drawer)(
		messages::move(
			cursor_id,
			screen_to_virtual(
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
			show
		)
	);
}
