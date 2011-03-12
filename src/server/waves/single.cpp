#include "single.hpp"
#include "spawn.hpp"

sanguis::server::waves::single::single(
	enemy_type::type const _etype
)
:
	etype_(_etype),
	spawned(false)
{}

void
sanguis::server::waves::single::process(
	time_type const,
	environment::object_ptr const _env,
	environment::load_context_ptr const _load_context
)
{
	spawn(
		_env,
		_load_context,
		etype_
	);

	spawned = true;
}

bool
sanguis::server::waves::single::ended() const
{
	return spawned;
}

