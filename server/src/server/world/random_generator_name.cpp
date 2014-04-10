#include <sanguis/random_generator.hpp>
#include <sanguis/creator/generator_count.hpp>
#include <sanguis/creator/generator_count_type.hpp>
#include <sanguis/creator/generator_index.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/server/world/random_generator_name.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_impl.hpp>


sanguis::creator::name
sanguis::server::world::random_generator_name(
	sanguis::random_generator &_generator
)
{
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::generator_count_type
		>
	> uniform_count;

	return
		sanguis::creator::generator_index(
			uniform_count(
				uniform_count::param_type::min(
					0u
				),
				uniform_count::param_type::max(
					sanguis::creator::generator_count() - 1u
				)
			)(
				_generator
			)
		);
}
