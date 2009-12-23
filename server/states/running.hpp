#ifndef SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED

#include "unpaused_fwd.hpp"
#include "../global/context_fwd.hpp"
#include "../message_event_fwd.hpp"
#include "../machine.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/player_cheat.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../messages/base_fwd.hpp"
#include "../../net/id_type.hpp"
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

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

	explicit running(
		my_context
	);

	~running();
	
	boost::statechart::result
	react(
		message_event const &
	);
	
	boost::statechart::result
	operator()(
		net::id_type,
		messages::connect const &
	);

	boost::statechart::result
	operator()(
		net::id_type,
		messages::disconnect const &
	);

	boost::statechart::result
	operator()(
		net::id_type,
		messages::client_info const &
	);

	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_cheat const &
	);

	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_choose_perk const &
	);

	global::context &
	global_context();
private:
	/*
	void level_callback(
		server::entities::player &,
		level_type);
	
	void send_available_perks(
		entities::player const &);
	
	*/

	boost::statechart::result
	handle_default_msg(
		net::id_type,
		messages::base const &
	);

	static fcppt::log::object
	&log();

	fcppt::scoped_ptr<
		global::context
	> global_context_;
	//pickup_spawner pickup_spawner_;

	/*sge::random::uniform<
		probability_type
	> pickup_chance_;*/

//	waves::generator wave_generator;

//	player_record_vector player_records;
};

}
}
}

#endif
