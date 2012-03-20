#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/translate/vector_from_client.hpp>
#include <sanguis/client/draw2d/translate/scalar_from_client.hpp>
#include <fcppt/algorithm/array_map.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::messages::types::vector2 const
sanguis::client::draw2d::translate::vector_from_client(
	draw2d::vector2 const &_vector
)
{
	return
		fcppt::math::vector::structure_cast<
			draw2d::vector2
		>(
			fcppt::algorithm::array_map<
				draw2d::vector2
			>(
				_vector,
				&translate::scalar_from_client
			)
		);
}
