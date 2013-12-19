#ifndef SANGUIS_GUI_WIDGET_TREE_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_TREE_HPP_INCLUDED

#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/reference_tree_vector.hpp>
#include <sanguis/gui/widget/tree_fwd.hpp>
#include <sanguis/gui/widget/unique_ptr_vector.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class tree
:
	public sanguis::gui::widget::box_container
{
	FCPPT_NONCOPYABLE(
		tree
	);
public:
	SANGUIS_GUI_SYMBOL
	tree(
		sanguis::gui::context &,
		sanguis::gui::widget::reference_tree_vector const &
	);

	SANGUIS_GUI_SYMBOL
	~tree();
private:
	sanguis::gui::widget::unique_ptr_vector boxes_;
};

}
}
}

#endif
