#include "spawn.hpp"

void
sanguis::server::entities::spawns::spawn::unregister(
	entities::base &
)
{
}

sanguis::server::entities::spawns::spawn::~spawn()
{
}

sanguis::server::entities::spawns::spawn::spawn(
	enemy_type::type const enemy_type_
)
:
	enemy_type_(enemy_type_)
{}

sanguis::entity_type::type
sanguis::server::entities::spawns::spawn::type() const
{
	return entity_type::spawn;
}

sanguis::server::team::type
sanguis::server::entities::spawns::spawn::team() const
{
	return server::team::monsters;
}

void
sanguis::server::entities::spawns::spawn::on_update(
	time_type const time_
)
{
	if(
		count const count_ =
			may_spawn(
				time_
			)
	)
	{
	/*
		waves::spawn(
			
		);	
	*/
	}
}
