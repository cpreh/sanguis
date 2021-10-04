#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_WEAPON_ATTRIBUTE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_WEAPON_ATTRIBUTE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/hover/weapon_attribute_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::client::draw2d::scene::hover
{

using
weapon_attribute_unique_ptr
=
fcppt::unique_ptr<
	sanguis::client::draw2d::scene::hover::weapon_attribute
>;

}

#endif
