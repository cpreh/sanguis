#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_ATTRIBUTE_VALUE_TO_STRING_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_ATTRIBUTE_VALUE_TO_STRING_HPP_INCLUDED

#include <sanguis/weapon_attribute_value.hpp>
#include <sge/font/string.hpp>

namespace sanguis::client::gui::hud
{

sge::font::string weapon_attribute_value_to_string(sanguis::weapon_attribute_value);

}

#endif
