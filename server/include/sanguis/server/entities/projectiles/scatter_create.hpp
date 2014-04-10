#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_SCATTER_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_SCATTER_CREATE_HPP_INCLUDED

#include <sanguis/server/angle_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

typedef
std::function<
	sanguis::server::entities::unique_ptr(
		sanguis::server::environment::object &,
		sanguis::server::team,
		sanguis::server::angle
	)
>
scatter_create;

}
}
}
}

#endif
