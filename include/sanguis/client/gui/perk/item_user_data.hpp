#ifndef SANGUIS_CLIENT_GUI_PERK_ITEM_USER_DATA_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_ITEM_USER_DATA_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>


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

sanguis::perk_type
item_user_data(
	CEGUI::TreeItem const &
);

}
}
}
}

#endif
