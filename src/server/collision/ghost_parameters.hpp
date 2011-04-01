#ifndef SANGUIS_SERVER_COLLISION_GHOST_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_PARAMETERS_HPP_INCLUDED

#include "ghost_parameters_fwd.hpp"
#include "global_groups_fwd.hpp"
#include "group_vector.hpp"
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class ghost_parameters
{
	FCPPT_NONASSIGNABLE(
		ghost_parameters
	);
public:
	ghost_parameters(
		sge::projectile::world &,
		collision::group_vector const &,
		collision::global_groups const &
	);

	sge::projectile::world &
	world() const;

	collision::group_vector const &
	groups() const;

	collision::global_groups const &
	global_groups() const;
private:
	sge::projectile::world &world_;

	collision::group_vector const groups_;

	collision::global_groups const &global_groups_;
};

}
}
}

#endif
