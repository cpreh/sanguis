#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/enemies/spawn_owner.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/waves/debug.hpp>
#include <sanguis/server/waves/spawn.hpp>
#include <sanguis/server/waves/wave.hpp>


sanguis::server::waves::debug::debug(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator
)
:
	sanguis::server::waves::wave(),
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
	sanguis::server::environment::object &_env,
	sanguis::server::environment::load_context &_load_context
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
		sanguis::server::waves::spawn(
			diff_clock_,
			random_generator_,
			_env,
			_load_context,
			static_cast<
				sanguis::enemy_type
			>(
				index
			),
			sanguis::server::entities::enemies::spawn_owner(
				sanguis::server::entities::auto_weak_link()
			)
		);

	spawned_ = true;
}

bool
sanguis::server::waves::debug::ended() const
{
	return spawned_;
}
