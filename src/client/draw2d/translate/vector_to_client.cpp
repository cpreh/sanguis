#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/translate/vector_to_client.hpp>
#include <sanguis/client/draw2d/translate/scalar_to_client.hpp>
#include <fcppt/algorithm/array_map.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::client::draw2d::vector2 const
sanguis::client::draw2d::translate::vector_to_client(
	messages::types::vector2 const &_vec
)
{
	return
		fcppt::math::vector::structure_cast<
			draw2d::vector2
		>(
			fcppt::algorithm::array_map<
				draw2d::vector2
			>(
				_vec,
				&translate::scalar_to_client
			)
		);
}
