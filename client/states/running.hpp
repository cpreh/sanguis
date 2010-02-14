#ifndef SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED

#include "menu.hpp"
#include "unpaused_fwd.hpp"
#include "../machine.hpp"
#include "../perk_chooser.hpp"
#include "../music_handler.hpp"
#include "../message_event_fwd.hpp"
#include "../perk_container.hpp"
#include "../level_type.hpp"
#include "../menu_event_fwd.hpp"
#include "../control/logic_fwd.hpp"
#include "../control/input_handler_fwd.hpp"
#include "../highscore/name_container.hpp"
#include "../highscore/score_type.hpp"
#include "../draw2d/scene/object_fwd.hpp"
#include "../draw2d/sprite/point.hpp"
#include "../../perk_type.hpp"
#include "../../tick_event_fwd.hpp"
#include "../../messages/base.hpp"
#include "../../messages/add_own_player.hpp"
#include "../../messages/highscore.hpp"
#include "../../messages/remove_id.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/available_perks.hpp"
#include "../../messages/level_up.hpp"
#include "../../entity_id.hpp"
#include <sge/renderer/state/scoped.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace client
{
namespace states
{

class running
:
	public boost::statechart::state<
		running,
		machine,
		unpaused
	>
{
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			message_event
		>,
		boost::statechart::transition<
			menu_event,
			menu
		>
	> reactions;

	explicit running(
		my_context
	);

	~running();

	void
	draw(
		tick_event const &
	);

	void
	process(
		tick_event const &
	);

	void
	pause(
		bool
	);

	boost::statechart::result
	react(
		message_event const &
	);
	
	typedef boost::statechart::result result_type;

	boost::statechart::result
	operator()(
		messages::add_own_player const &
	);

	boost::statechart::result
	operator()(
		messages::remove_id const &
	);

	boost::statechart::result
	operator()(
		messages::disconnect const &
	);

	boost::statechart::result
	operator()(
		messages::give_weapon const &
	);

	boost::statechart::result
	operator()(
		messages::highscore const &
	);

	boost::statechart::result
	operator()(
		messages::available_perks const &
	);

	boost::statechart::result
	operator()(
		messages::level_up const &
	);
	
	perk_container const &
	perks() const;
	
	level_type
	levels_left() const;
	
	void
	consume_level();

	entity_id
	player_id() const;

	client::perk_chooser &
	perk_chooser();
private:
	boost::statechart::result
	handle_default_msg(
		messages::base const &
	);

	void
	send_message(
		messages::auto_ptr
	);

	void
	send_perk_choose(
		perk_type::type
	);

	void
	cursor_pos(
		draw2d::sprite::point const & // FIXME!
	);

	void
	cursor_show(
		bool show
	);

	sge::renderer::state::scoped renderer_state_;

	music_handler music_;

	fcppt::scoped_ptr<
		draw2d::scene::object
	> drawer;

	fcppt::scoped_ptr<
		control::logic
	> logic_;

	fcppt::scoped_ptr<
		control::input_handler
	> input;

	fcppt::signal::auto_connection input_connection;

	client::perk_chooser perk_chooser_;

	entity_id const cursor_id;

	fcppt::signal::scoped_connection const
		cursor_pos_conn_,
		cursor_show_conn_,
		cheat_kill_conn_,
		cheat_impulse_conn_;
};
}
}
}

#endif
