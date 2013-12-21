#ifndef SANGUIS_CLIENT_GUI_PERK_TAB_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_TAB_HPP_INCLUDED

#include <sanguis/client/gui/perk/tab_fwd.hpp>
#include <sanguis/client/perk/const_tree_range.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/unique_ptr_tree_vector.hpp>
#include <sanguis/gui/widget/tree.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

class tab
{
	FCPPT_NONCOPYABLE(
		tab
	);
public:
	tab(
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::gui::context &,
		sanguis::client::perk::const_tree_range const &
	);

	~tab();

	sanguis::gui::widget::tree &
	widget();

	sge::font::string const &
	name() const;
private:
	sanguis::gui::widget::unique_ptr_tree_vector tree_widgets_;

	sanguis::gui::widget::tree tree_;

	sge::font::string const name_;
};

}
}
}
}

#endif
