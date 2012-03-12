#include <sanguis/server/global/world_context.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/messages/base_fwd.hpp>


sanguis::server::global::world_context::world_context(
	global::context &_global_context
)
:
	global_context_(_global_context)
{
}

sanguis::server::global::world_context::~world_context()
{
}

void
sanguis::server::global::world_context::transfer_entity(
	world_id const _destination,
	entities::unique_ptr _entity,
	entities::insert_parameters const &_insert_parameters
)
{
	global_context_.transfer_entity(
		_destination,
		move(
			_entity
		),
		_insert_parameters
	);
}

void
sanguis::server::global::world_context::send_to_player(
	player_id const _player_id,
	messages::base const &_msg
)
{
	global_context_.send_to_player(
		_player_id,
		_msg
	);
}

void
sanguis::server::global::world_context::remove_player(
	player_id const _player_id
)
{
	global_context_.remove_player(
		_player_id
	);
}
