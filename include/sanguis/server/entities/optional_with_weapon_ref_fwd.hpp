#ifndef SANGUIS_SERVER_ENTITIES_OPTIONAL_WITH_WEAPON_REF_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_OPTIONAL_WITH_WEAPON_REF_FWD_HPP_INCLUDED

#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

typedef
fcppt::optional<
	sanguis::server::entities::with_weapon &
>
optional_with_weapon_ref;

}
}
}

#endif
