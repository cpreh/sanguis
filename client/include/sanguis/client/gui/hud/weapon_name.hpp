#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_NAME_HPP_INCLUDED

#include <sanguis/weapon_type_fwd.hpp>
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
weapon_name(
	sanguis::weapon_type const &
);

}
}
}
}

#endif
