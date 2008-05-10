#ifndef SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED

#include "../machine.hpp"
#include "../send_callback.hpp"
#include "../console_print_callback.hpp"
#include "../entities/entity_fwd.hpp"
#include "../entities/fwd.hpp"
#include "../../console_timer.hpp"

#include <sge/time/timer.hpp>

#include <boost/mpl/list.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include <map>

namespace sanguis
{
namespace server
{
namespace states
{

class unpaused;

class running
	: public boost::statechart::state<running,machine,unpaused>
{
	public:
	typedef std::map<net::id_type, entities::player*> player_map;

	// callbacks (can be public so one thinks that they are a member function)
	send_callback send;
	console_print_callback console_print;

	running(my_context);
	sge::time::timer &enemy_timer();
	entities::entity_container &entities();
	const entities::entity_container &entities() const;
	entities::entity &insert_entity(entities::entity_ptr);
	player_map &players();
	const player_map &players() const;
	private:

	entities::entity_container entities_;
	player_map players_;
	
	// this is better suited here so it isn't out of sync after unpausing
	console_timer enemy_timer_;
};

}
}
}

#endif
