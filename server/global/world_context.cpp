#include "world_context.hpp"
#include "context.hpp"

sanguis::server::global::world_context::world_context(
	global::context &global_context_
)
:
	global_context_(global_context_)
{}

sanguis::server::global::world_context::~world_context()
{}

void
sanguis::server::global::world_context::transfer_entity(
	world_id const destination,
	entities::auto_ptr entity 
)
{
	global_context_.transfer_entity(
		destination,
		entity
	);
}

void
sanguis::server::global::world_context::send_to_player(
	player_id const player_id_,
	messages::auto_ptr msg
)
{
	global_context_.send_to_player(
		player_id_,
		msg
	);
}
