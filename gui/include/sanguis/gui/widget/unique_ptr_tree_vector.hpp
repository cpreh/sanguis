#ifndef SANGUIS_GUI_WIDGET_UNIQUE_PTR_TREE_VECTOR_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_UNIQUE_PTR_TREE_VECTOR_HPP_INCLUDED

#include <sanguis/gui/widget/unique_ptr_tree.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

typedef
std::vector<
	sanguis::gui::widget::unique_ptr_tree
>
unique_ptr_tree_vector;

}
}
}

#endif
