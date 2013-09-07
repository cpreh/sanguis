#ifndef SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
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
		sanguis::collision::world::object &,
		sanguis::creator::grid const &,
		sanguis::server::center const &,
		sanguis::server::angle
	);

	sanguis::collision::world::object &
	world() const;

	sanguis::creator::grid const &
	grid() const;

	sanguis::server::center const
	center() const;

	sanguis::server::angle const
	angle() const;
private:
	sanguis::collision::world::object &world_;

	sanguis::creator::grid const &grid_;

	sanguis::server::center const center_;

	sanguis::server::angle const angle_;
};

}
}
}

#endif
