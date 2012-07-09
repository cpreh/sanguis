#ifndef SANGUIS_CLIENT_GUI_PERK_NODE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_NODE_HPP_INCLUDED

#include <sanguis/client/gui/perk/node_variant.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/nonassignable.hpp>


namespace CEGUI
{
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

class node
{
	FCPPT_NONASSIGNABLE(
		node
	);
public:
	explicit node(
		gui::perk::node_variant const &
	);

	void
	add_item(
		CEGUI::TreeItem &
	) const;

	void
	remove_item(
		CEGUI::TreeItem &
	) const;
private:
	gui::perk::node_variant const impl_;
};

}
}
}
}

#endif
