#include <sanguis/creator/generator/randgen.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <fcppt/random/distribution/uniform_int_impl.hpp>
#include <fcppt/random/generator/minstd_rand_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


sanguis::creator::generator::randgen::randgen(
	sanguis::creator::generator::seed const &_seed
)
:
	generator_(
		fcppt::random::generator::minstd_rand::seed(
			_seed.get()
		)
	),
	distribution_(
		sanguis::creator::generator::randgen::int_distribution::min(
			std::numeric_limits<
				sanguis::creator::generator::randgen::result_type::value_type
			>::min()
		),
		sanguis::creator::generator::randgen::int_distribution::max(
			std::numeric_limits<
				sanguis::creator::generator::randgen::result_type::value_type
			>::max()
		)
	)
{
}

sanguis::creator::generator::randgen::~randgen()
{
}

sanguis::creator::generator::randgen::result_type const
sanguis::creator::generator::randgen::operator()()
{
	return
		sanguis::creator::generator::randgen::result_type(
			distribution_(
				generator_
			)
		);
}
