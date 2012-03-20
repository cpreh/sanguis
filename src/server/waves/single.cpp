#include <sanguis/server/waves/single.hpp>
#include <sanguis/server/waves/spawn.hpp>

sanguis::server::waves::single::single(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	enemy_type::type const _etype
)
:
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	etype_(
		_etype
	),
	spawned_(
		false
	)
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
		random_generator_,
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
