#include <sanguis/client/gui/perk/make_tabs.hpp>
#include <sanguis/client/gui/perk/state.hpp>
#include <sanguis/client/gui/perk/tab.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/gui/perk/tab_unique_ptr.hpp>
#include <sanguis/client/perk/state_ref.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_name_pair.hpp>
#include <sge/gui/widget/reference_name_vector.hpp>
#include <sge/gui/widget/tab_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/algorithm/map.hpp>

sanguis::client::gui::perk::state::state(
    sge::renderer::device::ffp_ref const _renderer,
    sge::font::object_ref const _font,
    sge::gui::context_ref const _context,
    sge::gui::style::const_reference const _style,
    sanguis::client::perk::state_ref const _state)
    : tabs_(sanguis::client::gui::perk::make_tabs(_renderer, _font, _context, _style, _state)),
      main_tab_(
          _context,
          _style,
          _renderer,
          _font,
          fcppt::algorithm::map<sge::gui::widget::reference_name_vector>(
              tabs_,
              [](sanguis::client::gui::perk::tab_unique_ptr const &_tab)
              {
                return sge::gui::widget::reference_name_pair(
                    sge::gui::widget::reference(_tab->widget()), sge::font::string{_tab->name()});
              }))
{
}

sanguis::client::gui::perk::state::~state() = default;

sge::gui::widget::tab &sanguis::client::gui::perk::state::widget() { return main_tab_; }
