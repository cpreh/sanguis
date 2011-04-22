#include "item_user_data.hpp"
#include <CEGUI/elements/CEGUITreeItem.h>

sanguis::perk_type::type
sanguis::client::gui::perk::item_user_data(
	CEGUI::TreeItem const &_item
)
{
	return
		*static_cast<
			sanguis::perk_type::type const *
		>(
			_item.getUserData()
		);
}
