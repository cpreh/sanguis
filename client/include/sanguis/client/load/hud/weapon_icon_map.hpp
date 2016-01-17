#ifndef SANGUIS_CLIENT_LOAD_HUD_WEAPON_ICON_MAP_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_HUD_WEAPON_ICON_MAP_HPP_INCLUDED

#include <sanguis/weapon_type.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/variant/less.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace hud
{

typedef
std::map<
	sanguis::weapon_type,
	fcppt::reference<
		sge::texture::part const
	>
>
weapon_icon_map;

}
}
}
}

#endif
