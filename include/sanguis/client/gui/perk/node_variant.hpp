#ifndef SANGUIS_CLIENT_GUI_PERK_NODE_VARIANT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_NODE_VARIANT_HPP_INCLUDED

#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace CEGUI
{
class Tree;
class TreeItem;
}

namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

typedef fcppt::variant::object<
	boost::mpl::vector2<
		CEGUI::Tree *,
		CEGUI::TreeItem *
	>
> node_variant;

}
}
}
}

#endif
