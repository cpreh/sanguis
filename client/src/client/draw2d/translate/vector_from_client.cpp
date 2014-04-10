#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/translate/vector_from_client.hpp>
#include <sanguis/client/draw2d/translate/scalar_from_client.hpp>
#include <sanguis/messages/types/vector2.hpp>
#include <fcppt/math/map.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::messages::types::vector2 const
sanguis::client::draw2d::translate::vector_from_client(
	sanguis::client::draw2d::vector2 const &_vector
)
{
	return
		fcppt::math::vector::structure_cast<
			sanguis::client::draw2d::vector2
		>(
			fcppt::math::map<
				sanguis::client::draw2d::vector2
			>(
				_vector,
				&sanguis::client::draw2d::translate::scalar_from_client
			)
		);
}
