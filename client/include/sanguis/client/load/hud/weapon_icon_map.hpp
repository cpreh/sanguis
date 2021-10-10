#ifndef SANGUIS_CLIENT_LOAD_HUD_WEAPON_ICON_MAP_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_HUD_WEAPON_ICON_MAP_HPP_INCLUDED

#include <sanguis/weapon_type.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/variant/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::load::hud
{

using weapon_icon_map = std::map<sanguis::weapon_type, fcppt::reference<sge::texture::part const>>;

}

#endif
