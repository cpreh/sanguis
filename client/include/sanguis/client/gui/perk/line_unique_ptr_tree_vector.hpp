#ifndef SANGUIS_CLIENT_GUI_PERK_LINE_UNIQUE_PTR_TREE_VECTOR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_LINE_UNIQUE_PTR_TREE_VECTOR_HPP_INCLUDED

#include <sanguis/client/gui/perk/line_unique_ptr_tree.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

using
line_unique_ptr_tree_vector
=
std::vector<
	sanguis::client::gui::perk::line_unique_ptr_tree
>;

}
}
}
}

#endif
