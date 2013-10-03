#ifndef SANGUIS_SERVER_WEAPONS_CONST_OPTIONAL_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CONST_OPTIONAL_REF_FWD_HPP_INCLUDED

#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

typedef
fcppt::optional<
	sanguis::server::weapons::weapon const &
>
const_optional_ref;

}
}
}

#endif
