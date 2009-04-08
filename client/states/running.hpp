#ifndef SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED

#include "unpaused_fwd.hpp"
#include "../perk_chooser.hpp"
#include "../music_handler.hpp"
#include "../message_event.hpp"
#include "../machine.hpp"
#include "../input_handler.hpp"
#include "../logic.hpp"
#include "../perk_container.hpp"
#include "../level_type.hpp"
#include "../../perk_type.hpp"
#include "../../tick_event.hpp"
#include "../../weapon_type.hpp"
#include "../../messages/base.hpp"
#include "../../messages/types/level.hpp"
#include "../../messages/assign_id.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/available_perks.hpp"
#include "../../messages/level_up.hpp"
#include "../../messages/move.hpp"
#include "../../messages/remove.hpp"
#include "../../draw/scene_fwd.hpp"
#include "../../draw/player_fwd.hpp"
#include <sge/signal/auto_connection.hpp>
#include <sge/scoped_ptr.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list.hpp>
#include <boost/array.hpp>
#include <vector>

namespace sanguis
{
namespace client
{
namespace states
{
class running
	: public boost::statechart::state<running,machine,unpaused>
{
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<message_event>
	> reactions;

	running(my_context);
	~running();
	void draw(tick_event const &);
	void process(tick_event const &);
	void pause(bool);
	boost::statechart::result react(message_event const &);
	
	boost::statechart::result operator()(
		messages::assign_id const &);
	boost::statechart::result operator()(
		messages::disconnect const &);
	boost::statechart::result operator()(
		messages::give_weapon const &);
	boost::statechart::result operator()(
		messages::move const &);
	boost::statechart::result operator()(
		messages::remove const &);

	boost::statechart::result operator()(
		messages::available_perks const &);
	boost::statechart::result operator()(
		messages::level_up const &);
	
	perk_container const &perks() const;
	level_type levels_left() const;
	void consume_level();
	entity_id player_id() const;
	client::perk_chooser &perk_chooser();
	private:
	boost::statechart::result handle_default_msg(
		messages::base const &);

	void send_message(
		messages::auto_ptr);
	void send_perk_choose(perk_type::type);

	music_handler music_;
	sge::scoped_ptr<
		draw::scene
	> drawer;
	logic logic_;
	input_handler input;
	sge::signal::auto_connection input_connection;
	client::perk_chooser perk_chooser_;
};
}
}
}

#endif
