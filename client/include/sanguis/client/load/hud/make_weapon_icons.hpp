#ifndef SANGUIS_CLIENT_LOAD_HUD_MAKE_WEAPON_ICONS_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_HUD_MAKE_WEAPON_ICONS_HPP_INCLUDED

#include <sanguis/client/load/hud/weapon_icon_map.hpp>
#include <sanguis/client/load/resource/textures_cref.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace hud
{

sanguis::client::load::hud::weapon_icon_map
make_weapon_icons(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	sanguis::client::load::resource::textures_cref
);

}
}
}
}

#endif
