#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <sanguis/creator/impl/random/uniform_pos.hpp>
#include <sanguis/creator/impl/random/uniform_pos_parameters.hpp>


sanguis::creator::impl::random::uniform_pos::uniform_pos(
	sanguis::creator::impl::random::generator &_generator,
	sanguis::creator::dim const _dim
)
:
	random_x_(
		_generator,
		sanguis::creator::impl::random::uniform_pos_parameters(
			_dim.w()
		)
	),
	random_y_(
		_generator,
		sanguis::creator::impl::random::uniform_pos_parameters(
			_dim.h()
		)
	)
{
}

sanguis::creator::pos
sanguis::creator::impl::random::uniform_pos::operator()()
{
	return
		sanguis::creator::pos(
			random_x_(),
			random_y_()
		);
}
