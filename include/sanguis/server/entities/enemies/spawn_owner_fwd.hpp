#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SPAWN_OWNER_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SPAWN_OWNER_FWD_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <sanguis/server/entities/auto_weak_link_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::entities::auto_weak_link,
	spawn_owner
);

}
}
}
}

#endif
