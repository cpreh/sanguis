#ifndef SANGUIS_SERVER_ENTITIES_GHOST_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_GHOST_PARAMETERS_HPP_INCLUDED

#include "ghost_parameters_fwd.hpp"
#include "global_groups_fwd.hpp"
#include "../center.hpp"
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class ghost_parameters
{
	FCPPT_NONASSIGNABLE(
		ghost_parameters
	);
public:
	ghost_parameters(
		sge::projectile::world &,
		collision::global_groups const &,
		server::center const &
	);

	sge::projectile::world &
	world() const;

	collision::global_groups const &
	global_groups() const;

	server::center const &
	center() const;
private:
	sge::projectile::world &world_;

	collision::global_groups const &global_groups_;

	server::center const center_;
};

}
}
}

#endif
