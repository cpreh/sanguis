#include "environment.hpp"
#include "object.hpp"
#include <sge/math/dim/basic_impl.hpp>

sanguis::server::world::environment::environment(
	world::object &world_
)
:
	world_(world_)
{}

sanguis::server::world::environment::~environment()
{}

sanguis::server::entities::entity & 
sanguis::server::world::environment::insert(
	entities::auto_ptr e
)
{
	return world_.insert(
		e
	);
}

void
sanguis::server::world::environment::weapon_changed(
	entity_id const id,
	weapon_type::type const wt
)
{
	world_.weapon_changed(
		id,
		wt
	);
}

void
sanguis::server::world::environment::got_weapon(
	entity_id const id,
	weapon_type::type const wt
)
{
	world_.got_weapon(
		id,
		wt
	);
}

void
sanguis::server::world::environment::attacking_changed(
	entity_id const id,
	bool const is_attacking
)
{
	world_.attacking_changed(
		id,
		is_attacking
	);
}

void
sanguis::server::world::environment::reloading_changed(
	entity_id const id,
	bool const is_reloading
)
{
	world_.reloading_changed(
		id,
		is_reloading
	);
}

void
sanguis::server::world::environment::max_health_changed(
	entity_id const id,
	health_type const health_
)
{
	world_.max_health_changed(
		id,
		health_
	);
}

void
sanguis::server::world::environment::remove_player(
	player_id const player_id_
)
{
	world_.remove_player(
		player_id_
	);
}

sge::collision::world_ptr const
sanguis::server::world::environment::collision_world() const
{
	return world_.collision_world();
}

sanguis::server::dim_type const
sanguis::server::world::environment::entity_dim(
	string const &model_name
) const
{
	return world_.entity_dim(
		model_name
	);
}
