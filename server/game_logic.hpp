#ifndef GAME_LOGIC_HPP_INCLUDED
#define GAME_LOGIC_HPP_INCLUDED

#include "../messages/fwd.hpp"
#include "../net/types.hpp"
#include "../console_timer.hpp"
#include "../tick_event.hpp"
#include "entity.hpp"
#include <sge/timer.hpp>
#include <boost/function.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
class player;
}

class game_logic
{
	public:
	typedef boost::function<void (messages::base *const)> send_callback;

	game_logic(send_callback);
	void add_enemy();
	void create_game(const net::id_type,const messages::client_info &);
	void process(const net::id_type,const messages::base &);
	entity &insert_entity(entity *);
	bool aborted() const { return aborted_; }

	// reactions
	void update(const time_type);
	void operator()(const net::id_type,const messages::client_info &);
	void operator()(const net::id_type,const messages::player_direction &);
	void operator()(const net::id_type,const messages::player_rotation &);
	void operator()(const net::id_type,const messages::player_start_shooting &);
	void operator()(const net::id_type,const messages::player_stop_shooting &);
	void operator()(const net::id_type,const messages::player_change_weapon &);
	void operator()(const net::id_type,const messages::disconnect &);
	void handle_default_msg(const net::id_type,const messages::base &);
	
	private:
	typedef boost::ptr_list<server::entity> entity_container;
	typedef std::map<net::id_type,entities::player*> player_map;

	send_callback send;
	entity_container entities;
	player_map players;
	bool aborted_;

	// timers
	console_timer send_timer;
	console_timer enemy_timer;
};
}
}

#endif
