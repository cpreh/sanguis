#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/value.hpp>
#include <fcppt/random/generator/minstd_rand_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


sanguis::creator::impl::random::generator::generator(
	sanguis::creator::seed const &_seed
)
:
	generator_(
		generator_type::seed(
			_seed.get()
		)
	)
{
	static_assert(
		std::numeric_limits<
			sanguis::creator::impl::random::value
		>::min()
		==
		generator_type::min(),
		"min does not match"
	);

	static_assert(
		std::numeric_limits<
			sanguis::creator::impl::random::value
		>::max()
		==
		generator_type::max(),
		"max does not match"
	);
}

sanguis::creator::impl::random::generator::~generator()
= default;

sanguis::creator::impl::random::generator::result_type
sanguis::creator::impl::random::generator::operator()()
{
	return
		static_cast<
			sanguis::creator::impl::random::generator::result_type
		>(
			generator_()
		);
}

sanguis::creator::impl::random::generator::result_type
sanguis::creator::impl::random::generator::min()
{
	return
		static_cast<
			sanguis::creator::impl::random::value
		>(
			generator_type::min()
		);
}

sanguis::creator::impl::random::generator::result_type
sanguis::creator::impl::random::generator::max()
{
	return
		static_cast<
			sanguis::creator::impl::random::value
		>(
			generator_type::max()
		);
}
