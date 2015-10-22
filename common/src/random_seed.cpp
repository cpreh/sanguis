#include <sanguis/random_generator.hpp>
#include <sanguis/random_seed.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>


sanguis::random_generator::seed
sanguis::random_seed()
{
	return
		fcppt::random::generator::seed_from_chrono<
			sanguis::random_generator::seed
		>();
}
