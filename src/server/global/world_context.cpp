#include <sanguis/world_id.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/global/world_context.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::global::world_context::world_context(
	sanguis::server::global::context &_global_context
)
:
	global_context_(
		_global_context
	)
{
}

sanguis::server::global::world_context::~world_context()
{
}

void
sanguis::server::global::world_context::transfer_entity(
	sanguis::world_id const _destination,
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
{
	global_context_.transfer_entity(
		_destination,
		std::move(
			_entity
		),
		_insert_parameters
	);
}

void
sanguis::server::global::world_context::send_to_player(
	sanguis::server::player_id const _player_id,
	sanguis::messages::base const &_msg
)
{
	global_context_.send_to_player(
		_player_id,
		_msg
	);
}

void
sanguis::server::global::world_context::remove_player(
	sanguis::server::player_id const _player_id
)
{
	global_context_.remove_player(
		_player_id
	);
}
