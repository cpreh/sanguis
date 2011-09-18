#include <sanguis/client/draw2d/translate/vector_to_client.hpp>
#include <sanguis/client/draw2d/translate/scalar_to_client.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/transform.hpp>

sanguis::client::draw2d::vector2 const
sanguis::client::draw2d::translate::vector_to_client(
	messages::types::vector2 const &_vec
)
{
	return
		fcppt::math::vector::structure_cast<
			draw2d::vector2
		>(
			fcppt::math::vector::transform(
				_vec,
				&translate::scalar_to_client
			)
		);
}
