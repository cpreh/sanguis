#ifndef SANGUIS_GUI_WIDGET_REFERENCE_TREE_FWD_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_REFERENCE_TREE_FWD_HPP_INCLUDED

#include <sanguis/gui/widget/reference.hpp>
#include <fcppt/container/tree/object_fwd.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

typedef
fcppt::container::tree::object<
	sanguis::gui::widget::reference
>
reference_tree;

}
}
}

#endif
