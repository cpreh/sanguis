#ifndef SANGUIS_CLIENT_GUI_PERK_ITEM_TREE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_ITEM_TREE_HPP_INCLUDED

#include <sanguis/client/gui/perk/item_fwd.hpp>
#include <fcppt/container/tree/object_fwd.hpp>
#include <fcppt/container/tree/ptr_value.hpp>

namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

typedef fcppt::container::tree::object<
	fcppt::container::tree::ptr_value<
		gui::perk::item
	>
> item_tree;

}
}
}
}

#endif
