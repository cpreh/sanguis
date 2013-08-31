#include <sanguis/perk_type.hpp>
#include <sanguis/client/gui/perk/item_user_data.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/widgets/TreeItem.h>
#include <fcppt/config/external_end.hpp>


sanguis::perk_type
sanguis::client::gui::perk::item_user_data(
	CEGUI::TreeItem const &_item
)
{
	return
		*fcppt::cast::from_void_ptr<
			sanguis::perk_type const *
		>(
			_item.getUserData()
		);
}
