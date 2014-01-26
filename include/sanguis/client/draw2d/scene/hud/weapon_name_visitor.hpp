#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HUD_WEAPON_NAME_VISITOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HUD_WEAPON_NAME_VISITOR_HPP_INCLUDED

#include <sanguis/primary_weapon_type_fwd.hpp>
#include <sanguis/secondary_weapon_type_fwd.hpp>
#include <sge/font/string.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace hud
{

struct weapon_name_visitor
{
	typedef
	sge::font::string
	result_type;

	result_type
	operator()(
		sanguis::primary_weapon_type
	) const;

	result_type
	operator()(
		sanguis::secondary_weapon_type
	) const;
};

}
}
}
}
}

#endif
