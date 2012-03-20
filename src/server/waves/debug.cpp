#include <sanguis/server/waves/debug.hpp>
#include <sanguis/server/waves/spawn.hpp>

sanguis::server::waves::debug::debug(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator
)
:
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	spawned_(
		false
	)
{
}

sanguis::server::waves::debug::~debug()
{
}

void
sanguis::server::waves::debug::process(
	environment::object &_env,
	environment::load_context &_load_context
)
{
	if(
		spawned_
	)
		return;

	for(
		unsigned index = 0;
		index < 2;
		++index
	)
		waves::spawn(
			diff_clock_,
			random_generator_,
			_env,
			_load_context,
			static_cast<
				enemy_type::type
			>(
				index
			)
		);

	spawned_ = true;
}

bool
sanguis::server::waves::debug::ended() const
{
	return spawned_;
}
