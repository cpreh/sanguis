#include <sanguis/client/gui/perk/make_tabs.hpp>
#include <sanguis/client/gui/perk/tab.hpp>
#include <sanguis/client/gui/perk/tab_unique_ptr_vector.hpp>
#include <sanguis/client/perk/category_equal_range.hpp>
#include <sanguis/client/perk/const_tree_range.hpp>
#include <sanguis/client/perk/state.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/perk/state_ref.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::client::gui::perk::tab_unique_ptr_vector sanguis::client::gui::perk::make_tabs(
    sge::renderer::device::ffp_ref const _renderer,
    sge::font::object_ref const _font,
    sge::gui::context_ref const _context,
    sge::gui::style::const_reference const _style,
    sanguis::client::perk::state_ref const _state)
{
  sanguis::client::perk::tree const &tree(_state->perks());

  sanguis::client::gui::perk::tab_unique_ptr_vector result{};

  for (sanguis::client::perk::const_tree_range range(
           sanguis::client::perk::category_equal_range(tree.begin(), tree.end()));
       !range.empty();
       range = sanguis::client::perk::category_equal_range(range.end(), tree.end()))
  {
    result.push_back(fcppt::make_unique_ptr<sanguis::client::gui::perk::tab>(
        _renderer, _font, _context, _style, _state, range));
  }

  return result;
}
