#include "single.hpp"
#include "spawn.hpp"

sanguis::server::waves::single::single(
	enemy_type::type const _etype
)
:
	etype_(_etype),
	spawned_(false)
{
}

sanguis::server::waves::single::~single()
{
}

void
sanguis::server::waves::single::process(
	time_type const,
	environment::object &_env,
	environment::load_context &_load_context
)
{
	waves::spawn(
		_env,
		_load_context,
		etype_
	);

	spawned_ = true;
}

bool
sanguis::server::waves::single::ended() const
{
	return spawned_;
}
