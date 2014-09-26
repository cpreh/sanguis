#ifndef SANGUIS_CLIENT_LOAD_HUD_WEAPON_TYPE_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_HUD_WEAPON_TYPE_HPP_INCLUDED

#include <sanguis/optional_weapon_type_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace hud
{

sanguis::optional_weapon_type const
weapon_type(
	fcppt::string const &
);

}
}
}
}

#endif
