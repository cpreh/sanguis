#ifndef SANGUIS_CLIENT_GUI_PERK_ITEM_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_ITEM_HPP_INCLUDED

#include "item_fwd.hpp"
#include "node.hpp"
#include "../object_fwd.hpp"
#include "../../perk/info_fwd.hpp"
#include "../../../perk_type.hpp"
#include <fcppt/noncopyable.hpp>
#include <elements/CEGUITreeItem.h>

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
		gui::perk::node const &,
		client::gui::object &,
		client::perk::info const &
	);

	~item();

	sanguis::perk_type::type
	perk_type() const;

	CEGUI::TreeItem &
	widget();
private:
	perk::node const parent_;

	sanguis::perk_type::type const perk_type_;

	CEGUI::TreeItem widget_;
};

}
}
}
}

#endif
