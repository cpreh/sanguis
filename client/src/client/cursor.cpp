#include <sanguis/client/cursor.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sge/cursor/hotspot.hpp>
#include <sge/input/const_processor_ref.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::client::cursor::cursor(
    sge::renderer::device::ffp_ref const _renderer,
    sge::input::const_processor_ref const _processor,
    sanguis::client::load::resource::textures_cref const _textures)
    : texture_(_textures->load(
          sanguis::client::load::resource::texture_identifier(FCPPT_TEXT("cursor")))),
      cursor_{
          _processor,
          _renderer,
          texture_,
          sge::cursor::hotspot{fcppt::math::vector::structure_cast<
              sge::cursor::hotspot::value_type,
              fcppt::cast::size_fun>(fcppt::math::dim::to_vector(
              (texture_->size() / fcppt::literal<sge::renderer::size_type>(2)).get_unsafe()))}}
{
}

sanguis::client::cursor::~cursor() = default;

void sanguis::client::cursor::draw(sge::renderer::context::ffp &_context)
{
  cursor_.draw(_context);
}
