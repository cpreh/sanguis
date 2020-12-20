#ifndef SANGUIS_CLIENT_GUI_PERK_LINE_UNIQUE_PTR_TREE_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_LINE_UNIQUE_PTR_TREE_FWD_HPP_INCLUDED

#include <sanguis/client/gui/perk/line_unique_ptr.hpp>
#include <fcppt/container/tree/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

using
line_unique_ptr_tree
=
fcppt::container::tree::object<
	sanguis::client::gui::perk::line_unique_ptr
>;

}
}
}
}

#endif
