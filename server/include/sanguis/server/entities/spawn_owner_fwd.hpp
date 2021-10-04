#ifndef SANGUIS_SERVER_ENTITIES_SPAWN_OWNER_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWN_OWNER_FWD_HPP_INCLUDED

#include <sanguis/server/entities/auto_weak_link_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis::server::entities
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::entities::auto_weak_link,
	spawn_owner
);

}

#endif
