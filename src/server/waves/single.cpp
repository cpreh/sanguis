#include "single.hpp"
#include "spawn.hpp"

sanguis::server::waves::single::single(
	sanguis::diff_clock const &_diff_clock,
	enemy_type::type const _etype
)
:
	diff_clock_(_diff_clock),
	etype_(_etype),
	spawned_(false)
{
}

sanguis::server::waves::single::~single()
{
}

void
sanguis::server::waves::single::process(
	environment::object &_env,
	environment::load_context &_load_context
)
{
	waves::spawn(
		diff_clock_,
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
