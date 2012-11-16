#include <sanguis/creator/generator/randgen.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/random/distribution/uniform_int_impl.hpp>
#include <fcppt/random/generator/minstd_rand_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

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
			this->min().get()
		),
		sanguis::creator::generator::randgen::int_distribution::max(
			this->max().get()
		)
	)
{
}

FCPPT_PP_POP_WARNING

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

sanguis::creator::generator::randgen::result_type const
sanguis::creator::generator::randgen::min() const
{
	return
		sanguis::creator::generator::randgen::result_type(
			std::numeric_limits<
				sanguis::creator::generator::randgen::result_type::value_type
			>::min()
		);
}

sanguis::creator::generator::randgen::result_type const
sanguis::creator::generator::randgen::max() const
{
	return
		sanguis::creator::generator::randgen::result_type(
			std::numeric_limits<
				sanguis::creator::generator::randgen::result_type::value_type
			>::max()
		);
}
