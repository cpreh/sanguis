#ifndef SANGUIS_GUI_WIDGET_TREE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_TREE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/gui/widget/tree_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

typedef
fcppt::unique_ptr<
	sanguis::gui::widget::tree
>
tree_unique_ptr;

}
}
}

#endif
