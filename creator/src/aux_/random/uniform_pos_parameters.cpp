#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/aux_/random/uniform_pos_parameters.hpp>
#include <sanguis/creator/aux_/random/uniform_size.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::creator::aux_::random::uniform_size::param_type
sanguis::creator::aux_::random::uniform_pos_parameters(
	sanguis::creator::size_type const _size
)
{
	FCPPT_ASSERT_PRE(
		_size
		>=
		3
	);

	return
		sanguis::creator::aux_::random::uniform_size::param_type(
			sanguis::creator::aux_::random::uniform_size::param_type::min(
				1u
			),
			sanguis::creator::aux_::random::uniform_size::param_type::max(
				_size - 2u
			)
		);
}
