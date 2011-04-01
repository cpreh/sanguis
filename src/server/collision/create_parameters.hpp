#ifndef SANGUIS_SERVER_COLLISION_CREATE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CREATE_PARAMETERS_HPP_INCLUDED

#include "create_parameters_fwd.hpp"
#include "global_groups_fwd.hpp"
#include "../center.hpp"
#include "../speed.hpp"
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class create_parameters
{
	FCPPT_NONASSIGNABLE(
		create_parameters
	);
public:
	create_parameters(
		sge::projectile::world &,
		server::center const &,
		server::speed const &,
		collision::global_groups const &
	);

	sge::projectile::world &
	world() const;

	server::center const
	center() const;

	server::speed const
	speed() const;

	collision::global_groups const &
	global_groups() const;
private:
	sge::projectile::world &world_;

	server::center const center_;

	server::speed const speed_;
	
	collision::global_groups const &global_groups_;
};

}
}
}

#endif
