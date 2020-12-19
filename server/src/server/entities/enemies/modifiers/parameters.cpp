#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters.hpp>


sanguis::server::entities::enemies::modifiers::parameters::parameters(
	sanguis::random_generator_ref const _random_generator
)
:
	random_generator_(
		_random_generator
	)
{
}

sanguis::random_generator &
sanguis::server::entities::enemies::modifiers::parameters::random_generator() const
{
	return
		random_generator_.get();
}
