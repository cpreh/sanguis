#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/enemies/spawn_owner.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/waves/single.hpp>
#include <sanguis/server/waves/wave.hpp>
#include <sanguis/server/waves/spawn.hpp>


sanguis::server::waves::single::single(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::enemy_type const _etype
)
:
	sanguis::server::waves::wave(),
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
	sanguis::server::environment::object &_env,
	sanguis::server::environment::load_context &_load_context
)
{
	sanguis::server::waves::spawn(
		diff_clock_,
		random_generator_,
		_env,
		_load_context,
		etype_,
		sanguis::server::entities::enemies::spawn_owner(
			sanguis::server::entities::auto_weak_link()
		)
	);

	spawned_ = true;
}

bool
sanguis::server::waves::single::ended() const
{
	return spawned_;
}
