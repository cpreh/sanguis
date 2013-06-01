#include <sanguis/creator/randgen.hpp>
#include <sanguis/creator/seed.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_impl.hpp>
#include <fcppt/random/generator/minstd_rand_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::creator::randgen::randgen(
	sanguis::creator::seed const &_seed
)
:
	generator_(
		fcppt::random::generator::minstd_rand::seed(
			_seed.get()
		)
	),
	distribution_(
		sanguis::creator::randgen::int_distribution::param_type::min(
			this->min()
		),
		sanguis::creator::randgen::int_distribution::param_type::max(
			this->max()
		)
	)
{
}

FCPPT_PP_POP_WARNING

sanguis::creator::randgen::~randgen()
{
}

sanguis::creator::randgen::result_type
sanguis::creator::randgen::operator()()
{
	return
		sanguis::creator::randgen::result_type(
			distribution_(
				generator_
			)
		);
}

sanguis::creator::randgen::result_type
sanguis::creator::randgen::min() const
{
	return
		sanguis::creator::randgen::result_type(
			std::numeric_limits<
				sanguis::creator::randgen::result_type
			>::min()
		);
}

sanguis::creator::randgen::result_type
sanguis::creator::randgen::max() const
{
	return
		sanguis::creator::randgen::result_type(
			std::numeric_limits<
				sanguis::creator::randgen::result_type
			>::max()
		);
}