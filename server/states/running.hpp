#ifndef SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED

#include "unpaused_fwd.hpp"
#include "../environment.hpp"
#include "../exp_type.hpp"
#include "../probability_type.hpp"
#include "../level_type.hpp"
#include "../message_event_fwd.hpp"
#include "../machine.hpp"
#include "../console_print_callback.hpp"
#include "../pickup_spawner.hpp"
#include "../entities/player_fwd.hpp"
#include "../entities/container.hpp"
#include "../entities/auto_ptr.hpp"
#include "../waves/generator.hpp"
#include "../../load/context_fwd.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../messages/base_fwd.hpp"
#include "../../net/id_type.hpp"
#include "../../time_type.hpp"
#include <sge/log/logger_fwd.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/random/uniform.hpp>
#include <sge/container/map_decl.hpp>
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
:
	public boost::statechart::state<
		running,
		machine,
		unpaused
>
{
public:
	typedef boost::statechart::custom_reaction<
		message_event
	> reactions;

	typedef sge::container::map<
		std::map,
		net::id_type,
		server::entities::player *
	> player_map;

	explicit running(
		my_context);
	
	server::entities::container &entities();
	server::entities::container const &entities() const;

	player_map &players();
	player_map const &players() const;

	entities::player &
	player(
		net::id_type);

	void process(
		time_type);

	server::environment const &
	environment() const;

	boost::statechart::result react(
		message_event const &);
	
	boost::statechart::result operator()(
		net::id_type,
		messages::connect const &);
	boost::statechart::result operator()(
		net::id_type,
		messages::disconnect const &);
	boost::statechart::result operator()(
		net::id_type,
		messages::client_info const &);
	boost::statechart::result operator()(
		net::id_type,
		messages::player_choose_perk const &);
private:
	void divide_exp(
		exp_type);

	void level_callback(
		server::entities::player &,
		level_type);
	
	server::entities::entity &
	insert_entity(
		server::entities::auto_ptr);
	
	send_callback const &
	send() const;

	bool
	pickup_chance(
		probability_type);

	boost::statechart::result
	handle_default_msg(
		net::id_type,
		messages::base const &);

	static sge::log::logger &log();

	server::environment const environment_;

	sge::signal::scoped_connection const coll_connection;

	console_print_callback const console_print;

	server::entities::container entities_;
	player_map players_;
	
	pickup_spawner pickup_spawner_;

	sge::random::uniform<
		probability_type
	> pickup_chance_;

	waves::generator wave_generator;
};

}
}
}

#endif
