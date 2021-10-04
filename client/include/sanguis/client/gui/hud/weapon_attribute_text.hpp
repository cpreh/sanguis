#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_ATTRIBUTE_TEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_ATTRIBUTE_TEXT_HPP_INCLUDED

#include <sanguis/weapon_attribute_fwd.hpp>
#include <sge/font/string.hpp>


namespace sanguis::client::gui::hud
{

sge::font::string
weapon_attribute_text(
	sanguis::weapon_attribute const &
);

}

#endif
