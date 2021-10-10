#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/translate/scalar_from_client.hpp>
#include <sanguis/client/draw2d/translate/vector_from_client.hpp>
#include <sanguis/messages/types/vector2.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::messages::types::vector2 sanguis::client::draw2d::translate::vector_from_client(
    sanguis::client::draw2d::vector2 const &_vector)
{
  return fcppt::math::vector::
      structure_cast<sanguis::client::draw2d::vector2, fcppt::cast::size_fun>(
          fcppt::math::vector::map(
              _vector, &sanguis::client::draw2d::translate::scalar_from_client));
}
