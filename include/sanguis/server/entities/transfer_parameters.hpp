#ifndef SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/collision/global_groups_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class transfer_parameters
{
	FCPPT_NONASSIGNABLE(
		transfer_parameters
	);
public:
	transfer_parameters(
		sge::projectile::world &,
		sanguis::server::center const &,
		sanguis::server::collision::global_groups const &,
		sanguis::server::angle
	);

	sge::projectile::world &
	world() const;

	sanguis::server::center const
	center() const;

	sanguis::server::collision::global_groups const &
	global_groups() const;

	sanguis::server::angle const
	angle() const;
private:
	sge::projectile::world &world_;

	sanguis::server::center const center_;

	sanguis::server::collision::global_groups const &global_groups_;

	sanguis::server::angle const angle_;
};

}
}
}

#endif
