#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/aux_/randgen.hpp>
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

sanguis::creator::aux_::randgen::randgen(
	sanguis::creator::seed const &_seed
)
:
	generator_(
		fcppt::random::generator::minstd_rand::seed(
			_seed.get()
		)
	),
	distribution_(
		sanguis::creator::aux_::randgen::int_distribution::param_type::min(
			this->min()
		),
		sanguis::creator::aux_::randgen::int_distribution::param_type::max(
			this->max()
		)
	)
{
}

FCPPT_PP_POP_WARNING

sanguis::creator::aux_::randgen::~randgen()
{
}

sanguis::creator::aux_::randgen::result_type
sanguis::creator::aux_::randgen::operator()()
{
	return
		sanguis::creator::aux_::randgen::result_type(
			distribution_(
				generator_
			)
		);
}

sanguis::creator::aux_::randgen::result_type
sanguis::creator::aux_::randgen::min() const
{
	return
		sanguis::creator::aux_::randgen::result_type(
			std::numeric_limits<
				sanguis::creator::aux_::randgen::result_type
			>::min()
		);
}

sanguis::creator::aux_::randgen::result_type
sanguis::creator::aux_::randgen::max() const
{
	return
		sanguis::creator::aux_::randgen::result_type(
			std::numeric_limits<
				sanguis::creator::aux_::randgen::result_type
			>::max()
		);
}
