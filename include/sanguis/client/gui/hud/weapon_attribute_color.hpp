#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_ATTRIBUTE_COLOR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_ATTRIBUTE_COLOR_HPP_INCLUDED

#include <sanguis/weapon_attribute_type_fwd.hpp>
#include <sge/image/color/any/object.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace hud
{

sge::image::color::any::object const
weapon_attribute_color(
	sanguis::weapon_attribute_type
);

}
}
}
}

#endif
