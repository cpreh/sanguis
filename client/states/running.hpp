#ifndef SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_RUNNING_HPP_INCLUDED

#include "unpaused_fwd.hpp"
#include "../music_handler.hpp"
#include "../message_event.hpp"
#include "../machine.hpp"
#include "../input_handler.hpp"
#include "../logic.hpp"
#include "../../perk_type.hpp"
#include "../../tick_event.hpp"
#include "../../weapon_type.hpp"
#include "../../messages/fwd.hpp"
#include "../../messages/base.hpp"
#include "../../messages/entity_message.hpp"
#include "../../draw/scene.hpp"
#include "../../draw/player_fwd.hpp"
#include <sge/signal/auto_connection.hpp>
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

	typedef std::vector<perk_type::type> perk_container;

	running(my_context);
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
	messages::level_type levels_left() const;
	void consume_level();
	entity_id player_id() const;
	private:
	boost::statechart::result handle_default_msg(
		messages::base const &);

	void send_message(
		messages::auto_ptr);

	music_handler                   music_;
	draw::scene                     drawer;
	logic                           logic_;
	input_handler                   input;
	sge::signal::auto_connection    input_connection;
	perk_container                  perks_;
	messages::level_type            current_level_,consumed_levels_;
};
}
}
}

#endif
