#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_ATTRIBUTE_DIFF_TO_STRING_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_ATTRIBUTE_DIFF_TO_STRING_HPP_INCLUDED

#include <sanguis/weapon_attribute_value.hpp>
#include <sge/font/string.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace hud
{

sge::font::string
weapon_attribute_diff_to_string(
	sanguis::weapon_attribute_value
);

}
}
}
}

#endif
