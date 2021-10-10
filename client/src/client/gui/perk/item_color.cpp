#include <sanguis/client/gui/perk/item_color.hpp>
#include <sanguis/client/perk/choosable_state.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::gui::text_color
sanguis::client::gui::perk::item_color(sanguis::client::perk::choosable_state const _state)
{
  switch (_state)
  {
  case sanguis::client::perk::choosable_state::ok:
    return sge::gui::text_color{sge::image::color::any::object{sge::image::color::predef::white()}};
  case sanguis::client::perk::choosable_state::parent_level:
  case sanguis::client::perk::choosable_state::player_level:
    return sge::gui::text_color{sge::image::color::any::object{sge::image::color::predef::red()}};
  case sanguis::client::perk::choosable_state::max_level:
    return sge::gui::text_color{sge::image::color::any::object{sge::image::color::predef::blue()}};
  case sanguis::client::perk::choosable_state::level_up:
    return sge::gui::text_color{sge::image::color::any::object{sge::image::color::predef::black()}};
  }

  FCPPT_ASSERT_UNREACHABLE;
}
