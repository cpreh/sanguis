#include "vector_from_client.hpp"
#include "scalar_from_client.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/transform.hpp>

sanguis::messages::types::vector2 const
sanguis::client::draw2d::translate::vector_from_client(
	draw2d::vector2 const &_vector
)
{
	return
		fcppt::math::vector::structure_cast<
			draw2d::vector2
		>(
			fcppt::math::vector::transform(
				_vector,
				&translate::scalar_from_client
			)
		);
}
