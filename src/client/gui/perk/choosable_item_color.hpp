#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSABLE_ITEM_COLOR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSABLE_ITEM_COLOR_HPP_INCLUDED

#include "../../perk/choosable_state.hpp"
#include <sge/image/color/any/object.hpp>

namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

sge::image::color::any::object const
choosable_item_color(
	client::perk::choosable_state::type
);

}
}
}
}

#endif
