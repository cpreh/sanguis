#include <sanguis/exception.hpp>
#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/background_texture_coordinates.hpp>
#include <sanguis/client/draw2d/sprite/client/texture_coordinates.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/tuple/element.hpp>
#include <fcppt/tuple/get.hpp>

sanguis::client::draw2d::sprite::client::texture_coordinates
sanguis::client::draw2d::scene::background_texture_coordinates(
    sanguis::client::draw2d::translation const &_translation,
    sge::renderer::device::core &_device,
    sge::texture::part const &_texture)
{
  using coordinates = sanguis::client::draw2d::sprite::client::texture_coordinates;

  using pos_type = fcppt::tuple::element<0U, coordinates>;

  auto const dim{fcppt::math::vector::structure_cast<pos_type, fcppt::cast::int_to_float_fun>(
      fcppt::math::dim::to_vector(sanguis::client::draw2d::scene::background_dim(_device)))};

  pos_type const divided{fcppt::optional::to_exception(
      dim / fcppt::math::vector::structure_cast<pos_type, fcppt::cast::int_to_float_fun>(
                fcppt::math::dim::to_vector(_texture.size())),
      [] { return sanguis::exception{FCPPT_TEXT("Empty texture!")}; })};

  coordinates const base(
      fcppt::math::vector::null<pos_type>(), divided);

  pos_type const rel_divided{fcppt::optional::to_exception(
      fcppt::math::vector::structure_cast<pos_type, fcppt::cast::size_fun>(-_translation.get()) /
          dim,
      [] { return sanguis::exception{FCPPT_TEXT("Empty dim!")}; })};

  pos_type const rel{rel_divided * fcppt::tuple::get<1U>(base)};

  return coordinates(fcppt::tuple::get<0U>(base) + rel, fcppt::tuple::get<1U>(base) + rel);
}
