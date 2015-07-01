#ifndef SANGUIS_CLIENT_GUI_PERK_ITEM_COLOR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_ITEM_COLOR_HPP_INCLUDED

#include <sanguis/client/perk/choosable_state_fwd.hpp>
#include <sge/gui/text_color.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

sge::gui::text_color
item_color(
	sanguis::client::perk::choosable_state
);

}
}
}
}

#endif
