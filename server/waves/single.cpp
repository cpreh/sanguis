#include "single.hpp"
#include "spawn.hpp"

sanguis::server::waves::single::single(
	enemy_type::type const etype_
)
:
	etype_(etype_),
	spawned(false)
{}

void
sanguis::server::waves::single::process(
	time_type const,
	environment::object_ptr const env,
	environment::load_context_ptr const load_context
)
{
	spawn(
		env,
		load_context,
		etype_
	);

	spawned = true;
}

bool
sanguis::server::waves::single::ended() const
{
	return spawned;
}

