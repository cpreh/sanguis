#ifndef SANGUIS_GUI_WIDGET_UNIQUE_PTR_TREE_FWD_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_UNIQUE_PTR_TREE_FWD_HPP_INCLUDED

#include <sanguis/gui/widget/unique_ptr.hpp>
#include <fcppt/container/tree/object_fwd.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

typedef
fcppt::container::tree::object<
	sanguis::gui::widget::unique_ptr
>
unique_ptr_tree;

}
}
}

#endif
