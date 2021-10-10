#include <sanguis/client/console/gfx.hpp>
#include <sge/console/object_ref.hpp>
#include <sge/console/gfx/font_color.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/output_line_limit.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/rect.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>

namespace
{

sge::font::rect make_console_rect(sge::renderer::target::viewport const &_viewport);

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::console::gfx::gfx(
    sge::console::object_ref const _console,
    sge::renderer::device::ffp_ref const _renderer,
    sge::font::object_ref const _font_object,
    sge::viewport::manager_ref const _viewport_manager,
    sge::console::gfx::output_line_limit const _history_size)
    : // TODO(philipp): Add a background again
      impl_(
          _console,
          _renderer,
          sge::console::gfx::font_color(
              sge::image::color::any::object{sge::image::color::predef::white()}),
          _font_object,
          ::make_console_rect(_renderer->onscreen_target().viewport()),
          _history_size),
      resize_connection_(_viewport_manager->manage_callback(
          sge::viewport::manage_callback{[this](sge::renderer::target::viewport const &_viewport)
                                         { this->on_resize(_viewport); }}))
{
}

FCPPT_PP_POP_WARNING

sanguis::client::console::gfx::~gfx() = default;

sge::console::gfx::object &sanguis::client::console::gfx::get() { return impl_; }

void sanguis::client::console::gfx::on_resize(sge::renderer::target::viewport const &_viewport)
{
  impl_.area(::make_console_rect(_viewport));
}

namespace
{

sge::font::rect make_console_rect(sge::renderer::target::viewport const &_viewport)
{
  sge::renderer::pixel_rect::dim const viewport_dim(_viewport.get().size());

  return sge::font::rect{
      fcppt::math::vector::null<sge::font::rect::vector>(),
      sge::font::rect::dim{
          fcppt::cast::size<sge::font::rect::value_type>(viewport_dim.w()),
          fcppt::cast::size<sge::font::rect::value_type>(
              viewport_dim.h() / fcppt::literal<sge::renderer::pixel_unit>(2))}};
}

}
