#ifndef SANGUIS_CLIENT_GUI_PERK_ITEM_COLOR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_ITEM_COLOR_HPP_INCLUDED

#include <sanguis/client/perk/choosable_state.hpp>
#include <sge/image/color/any/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

sge::image::color::any::object const
item_color(
	sanguis::client::perk::choosable_state::type
);

}
}
}
}

#endif
