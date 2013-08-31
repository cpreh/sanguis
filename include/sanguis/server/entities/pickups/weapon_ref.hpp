#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_REF_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_WEAPON_REF_HPP_INCLUDED

#include <sanguis/server/entities/pickups/weapon_fwd.hpp>
#include <fcppt/reference_wrapper_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

typedef
fcppt::reference_wrapper<
	sanguis::server::entities::pickups::weapon
>
weapon_ref;

}
}
}
}

#endif
