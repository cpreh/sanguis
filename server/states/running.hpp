#ifndef SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED

#include "../machine.hpp"
#include "../send_callback.hpp"
#include "../console_print_callback.hpp"
#include "../entities/entity_fwd.hpp"
#include "../entities/fwd.hpp"
#include "../waves/generator.hpp"
#include "../../messages/types.hpp"
#include "../../messages/fwd.hpp"
#include "../../time_type.hpp"
#include <sge/log/fwd.hpp>
#include <boost/mpl/list.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include <map>

namespace sanguis
{
namespace server
{

struct message_event;

namespace states
{

class unpaused;

class running
	: public boost::statechart::state<running,machine,unpaused>
{
public:
	typedef boost::statechart::custom_reaction<
		message_event
	> reactions;

	typedef std::map<
		net::id_type,
		server::entities::player*>
	player_map;

	running(
		my_context);
	
	server::entities::container &entities();
	server::entities::container const &entities() const;

	server::entities::entity &
	insert_entity(
		server::entities::auto_ptr);
	
	player_map &players();
	player_map const &players() const;

	void divide_exp(
		messages::exp_type);

	void level_callback(
		server::entities::player &,
		messages::level_type);

	void process(
		time_type);

	environment const get_environment();

	boost::statechart::result react(
		message_event const &);
	
	boost::statechart::result operator()(
		net::id_type,
		messages::connect const &);
	boost::statechart::result operator()(
		net::id_type,
		messages::client_info const &);
	boost::statechart::result operator()(
		net::id_type,
		messages::player_choose_perk const &);
private:
	boost::statechart::result handle_default_msg(
		net::id_type,
		messages::base const &);
	void create_decorations();
	static sge::log::logger &log();

	send_callback send;
	console_print_callback console_print;

	server::entities::container entities_;
	player_map players_;
	
	waves::generator wave_generator;
};

}
}
}

#endif
