#ifndef SANGUIS_SERVER_GAME_LOGIC_HPP_INCLUDED
#define SANGUIS_SERVER_GAME_LOGIC_HPP_INCLUDED

#include "../messages/fwd.hpp"
#include "../net/types.hpp"
#include "../console_timer.hpp"
#include "../time_type.hpp"
#include "entities/fwd.hpp"
#include "entity.hpp"
#include "send_callback.hpp"
#include "insert_callback.hpp"

namespace sanguis
{
namespace server
{

class game_logic
{
	public:
	game_logic(send_callback);
	void add_enemy();
	void create_game(const net::id_type,const messages::client_info &);
	void process(const net::id_type,const messages::base &);
	entity &insert_entity(entity_ptr);
	bool aborted() const;

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
	insert_callback get_insert_callback();
	send_callback get_send_callback();

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
