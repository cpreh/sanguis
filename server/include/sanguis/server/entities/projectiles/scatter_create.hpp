#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_SCATTER_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_SCATTER_CREATE_HPP_INCLUDED

#include <sanguis/server/angle_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis::server::entities::projectiles
{

using
scatter_create
=
fcppt::function<
	sanguis::server::entities::with_id_unique_ptr(
		sanguis::server::environment::object &,
		sanguis::server::team,
		sanguis::server::angle
	)
>;

}

#endif
