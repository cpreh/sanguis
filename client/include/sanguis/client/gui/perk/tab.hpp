#ifndef SANGUIS_CLIENT_GUI_PERK_TAB_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_TAB_HPP_INCLUDED

#include <sanguis/client/gui/perk/line_unique_ptr_tree_vector.hpp>
#include <sanguis/client/gui/perk/tab_fwd.hpp> // IWYU pragma: keep
#include <sanguis/client/perk/const_tree_range_fwd.hpp>
#include <sanguis/client/perk/state_ref.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/tree.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::gui::perk
{

class tab
{
  FCPPT_NONMOVABLE(tab);

public:
  tab(sge::renderer::device::ffp_ref,
      sge::font::object_ref,
      sge::gui::context_ref,
      sge::gui::style::const_reference,
      sanguis::client::perk::state_ref,
      sanguis::client::perk::const_tree_range const &);

  ~tab();

  [[nodiscard]] sge::gui::widget::tree &widget();

  [[nodiscard]] sge::font::string const &name() const;

private:
  sanguis::client::gui::perk::line_unique_ptr_tree_vector tree_widgets_;

  sge::gui::widget::tree tree_;

  sge::font::string const name_;
};

}

#endif
