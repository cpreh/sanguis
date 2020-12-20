#include <sanguis/random_generator.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/server/world/random_seed.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_impl.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


sanguis::creator::seed
sanguis::server::world::random_seed(
	sanguis::random_generator &_generator
)
{
	using
	uniform_seed
	=
	fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::seed
		>
	>;

	return
		uniform_seed(
			uniform_seed::param_type::min(
				sanguis::creator::seed(
					std::numeric_limits<
						sanguis::creator::seed::value_type
					>::min()
				)
			),
			uniform_seed::param_type::max(
				sanguis::creator::seed(
					std::numeric_limits<
						sanguis::creator::seed::value_type
					>::max()
				)
			)
		)(
			_generator
		);
}
