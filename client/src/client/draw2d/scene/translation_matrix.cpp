#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/scene/translation_matrix.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/vector/push_back.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sge::renderer::matrix4
sanguis::client::draw2d::scene::translation_matrix(
	sanguis::client::draw2d::translation const _translation
)
{
	return
		fcppt::math::matrix::translation(
			fcppt::math::vector::push_back(
				fcppt::math::vector::structure_cast<
					sanguis::client::draw2d::vector2,
					fcppt::cast::int_to_float_fun
				>(
					_translation.get()
				),
				fcppt::literal<
					sanguis::client::draw2d::funit
				>(
					0
				)
			)
		);
}
