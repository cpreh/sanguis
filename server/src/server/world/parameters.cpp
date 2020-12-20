#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/load_context_ref.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <sanguis/server/world/context_ref.hpp>
#include <sanguis/server/world/parameters.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/context_reference.hpp>


sanguis::server::world::parameters::parameters(
	fcppt::log::context_reference const _log_context,
	sanguis::random_generator_ref const _random_generator,
	sanguis::server::weapons::common_parameters const &_weapon_parameters,
	sanguis::server::world::context_ref const _context,
	sanguis::server::environment::load_context_ref const _load_context
)
:
	log_context_{
		_log_context
	},
	random_generator_(
		_random_generator
	),
	weapon_parameters_{
		_weapon_parameters
	},
	context_(
		_context
	),
	load_context_(
		_load_context
	)
{
}

fcppt::log::context &
sanguis::server::world::parameters::log_context() const
{
	return
		log_context_.get();
}

sanguis::random_generator &
sanguis::server::world::parameters::random_generator() const
{
	return
		random_generator_.get();
}

sanguis::server::weapons::common_parameters const &
sanguis::server::world::parameters::weapon_parameters() const
{
	return
		weapon_parameters_;
}

sanguis::server::world::context &
sanguis::server::world::parameters::context() const
{
	return
		context_.get();
}

sanguis::server::environment::load_context &
sanguis::server::world::parameters::load_context() const
{
	return
		load_context_.get();
}
