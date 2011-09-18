#ifndef SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/collision/global_groups_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
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
		server::center const &,
		collision::global_groups const &,
		server::angle
	);

	sge::projectile::world &
	world() const;

	server::center const
	center() const;

	collision::global_groups const &
	global_groups() const;

	server::angle const
	angle() const;
private:
	sge::projectile::world &world_;

	server::center const center_;

	collision::global_groups const &global_groups_;

	server::angle const angle_;
};

}
}
}

#endif
