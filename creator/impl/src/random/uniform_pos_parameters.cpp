#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/impl/random/uniform_pos_parameters.hpp>
#include <sanguis/creator/impl/random/uniform_size.hpp>
#include <fcppt/text.hpp>


sanguis::creator::impl::random::uniform_size::param_type
sanguis::creator::impl::random::uniform_pos_parameters(
	sanguis::creator::size_type const _size
)
{
	if(
		_size
		<
		3
	)
	{
		throw
			sanguis::creator::exception{
				FCPPT_TEXT("uniform_pos_parameters: size must be at least 3")
			};
	}

	return
		sanguis::creator::impl::random::uniform_size::param_type(
			sanguis::creator::impl::random::uniform_size::param_type::min(
				1U
			),
			sanguis::creator::impl::random::uniform_size::param_type::max(
				_size - 2U
			)
		);
}
