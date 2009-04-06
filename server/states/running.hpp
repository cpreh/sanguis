#ifndef SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED

#include "unpaused_fwd.hpp"
#include "../exp_type.hpp"
#include "../level_type.hpp"
#include "../message_event_fwd.hpp"
#include "../machine.hpp"
#include "../send_callback.hpp"
#include "../console_print_callback.hpp"
#include "../entities/player_fwd.hpp"
#include "../entities/container.hpp"
#include "../entities/auto_ptr.hpp"
#include "../waves/generator.hpp"
#include "../../load/context_fwd.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../messages/base_fwd.hpp"
#include "../../net/id_type.hpp"
#include "../../time_type.hpp"
#include <sge/log/logger_fwd.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/collision/satellite_fwd.hpp>
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
class running
	: public boost::statechart::state<running,machine,unpaused>
{
public:
	typedef boost::statechart::custom_reaction<
		message_event
	> reactions;

	typedef std::map<
		net::id_type,
		server::entities::player *
	> player_map;

	running(
		my_context);
	
	server::entities::container &entities();
	server::entities::container const &entities() const;

	server::entities::entity &
	insert_entity(
		server::entities::auto_ptr);
	
	player_map &players();
	player_map const &players() const;

	entities::player &
	player(
		net::id_type);

	void divide_exp(
		exp_type);

	void level_callback(
		server::entities::player &,
		level_type);
	
	bool collision_test(
		sge::collision::satellite const &,
		sge::collision::satellite const &);

	void collision(
		sge::collision::satellite &,
		sge::collision::satellite &);

	load::context const &
	load_callback() const;

	void process(
		time_type);

	server::environment const environment();

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

	sge::signal::auto_connection coll_connection;

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
