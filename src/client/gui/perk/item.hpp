#ifndef SANGUIS_CLIENT_GUI_PERK_ITEM_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_ITEM_HPP_INCLUDED

#include "item_fwd.hpp"
#include "../object_fwd.hpp"
#include "../../../perk_type.hpp"
#include <CEGUI/elements/CEGUITreeItem.h>
#include <fcppt/noncopyable.hpp>

namespace CEGUI
{
class Tree;
}

namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

class item
{
	FCPPT_NONCOPYABLE(
		item
	);
public:
	item(
		CEGUI::Tree &,
		client::gui::object &,
		sanguis::perk_type::type
	);

	~item();
private:
	CEGUI::Tree &tree_;

	sanguis::perk_type::type const perk_type_;

	CEGUI::TreeItem widget_;
};

}
}
}
}

#endif
