#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/client/gui/hud/weapon_details.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip_unique_ptr.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/optional/map.hpp>

sanguis::client::gui::hud::weapon_details::weapon_details(
    sge::gui::context_ref const _gui_context,
    sge::gui::style::const_reference const _gui_style,
    sge::renderer::device::ffp_ref const _renderer,
    sge::font::object_ref const _font,
    sanguis::optional_weapon_description const &_weapon1,
    sanguis::optional_weapon_description const &_weapon2)
    : tooltips_(fcppt::algorithm::map_optional<tooltip_vector>(
          fcppt::array::object<sanguis::optional_weapon_description, 2>{_weapon1, _weapon2},
          [&_gui_context, &_gui_style, &_renderer, &_font](
              sanguis::optional_weapon_description const &_desc)
          {
            return fcppt::optional::map(
                _desc,
                [&_gui_context, &_gui_style, &_renderer, &_font](
                    sanguis::weapon_description const &_ndesc)
                {
                  return fcppt::make_unique_ptr<sanguis::client::gui::hud::weapon_tooltip>(
                      _gui_context, _gui_style, _renderer, _font, _ndesc);
                });
          })),
      container_(
          _gui_context,
          fcppt::algorithm::map<sge::gui::widget::reference_alignment_vector>(
              tooltips_,
              [](sanguis::client::gui::hud::weapon_tooltip_unique_ptr const &_tooltip)
              {
                return sge::gui::widget::reference_alignment_pair(
                    sge::gui::widget::reference(_tooltip->widget()),
                    sge::rucksack::alignment::left_or_top);
              }),
          sge::rucksack::axis::y)
{
}

sanguis::client::gui::hud::weapon_details::~weapon_details() = default;

sge::gui::widget::base &sanguis::client::gui::hud::weapon_details::widget() { return container_; }
