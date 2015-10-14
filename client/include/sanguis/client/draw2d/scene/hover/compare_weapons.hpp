#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_COMPARE_WEAPONS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_COMPARE_WEAPONS_HPP_INCLUDED

#include <sanguis/weapon_attribute_fwd.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/client/weapon_pair_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute_diff.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace hover
{

sanguis::client::draw2d::scene::hover::weapon_attribute_diff
compare_weapons(
	sanguis::weapon_type,
	sanguis::weapon_attribute const &,
	sanguis::client::weapon_pair const &
);

}
}
}
}
}

#endif
