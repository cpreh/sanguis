#include <sanguis/client/gui/perk/item_user_data.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/widgets/TreeItem.h>
#include <fcppt/config/external_end.hpp>

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
