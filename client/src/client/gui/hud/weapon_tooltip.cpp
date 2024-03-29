#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/client/gui/default_text_color.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_color.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_name.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_text.hpp>
#include <sanguis/client/gui/hud/weapon_name.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/gui/widget/static_text.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/join.hpp>

sanguis::client::gui::hud::weapon_tooltip::weapon_tooltip(
    sge::gui::context_ref const _gui_context,
    sge::gui::style::const_reference const _gui_style,
    sge::renderer::device::ffp_ref const _renderer,
    sge::font::object_ref const _font,
    sanguis::weapon_description const &_description)
    : name_text_(
          _gui_style,
          _renderer,
          _font,
          sanguis::client::gui::hud::weapon_name(_description.weapon_type()),
          sanguis::client::gui::default_text_color()),
      attribute_texts_(fcppt::algorithm::map<text_unique_ptr_vector>(
          _description.attributes(),
          [&_gui_style, &_renderer, &_font](sanguis::weapon_attribute const &_attribute)
          {
            return fcppt::make_unique_ptr<sge::gui::widget::static_text>(
                _gui_style,
                _renderer,
                _font,
                sanguis::client::gui::hud::weapon_attribute_text(_attribute) + SGE_FONT_LIT(' ') +
                    sanguis::client::gui::hud::weapon_attribute_name(_attribute.type()),
                sanguis::client::gui::hud::weapon_attribute_color());
          })),
      container_(
          _gui_context,
          fcppt::container::join(
              sge::gui::widget::reference_alignment_vector{
                  sge::gui::widget::reference_alignment_pair(
                      sge::gui::widget::reference(name_text_),
                      sge::rucksack::alignment::left_or_top)},
              fcppt::algorithm::map<sge::gui::widget::reference_alignment_vector>(
                  attribute_texts_,
                  [](text_unique_ptr const &_text)
                  {
                    return sge::gui::widget::reference_alignment_pair(
                        sge::gui::widget::reference(*_text), sge::rucksack::alignment::left_or_top);
                  })),
          sge::rucksack::axis::y)
{
}

sanguis::client::gui::hud::weapon_tooltip::~weapon_tooltip() = default;

sge::gui::widget::base &sanguis::client::gui::hud::weapon_tooltip::widget() { return container_; }
