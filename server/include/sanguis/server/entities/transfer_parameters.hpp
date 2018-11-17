#ifndef SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/log_fwd.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class transfer_parameters
{
public:
	transfer_parameters(
		sanguis::collision::log const &,
		sanguis::collision::world::object &,
		sanguis::collision::world::created,
		sanguis::creator::grid const &,
		sanguis::server::center const &,
		sanguis::server::angle
	);

	sanguis::collision::log const &
	log() const;

	sanguis::collision::world::object &
	world() const;

	sanguis::collision::world::created
	created() const;

	sanguis::creator::grid const &
	grid() const;

	sanguis::server::center
	center() const;

	sanguis::server::angle
	angle() const;
private:
	fcppt::reference<
		sanguis::collision::log const
	> log_;

	fcppt::reference<
		sanguis::collision::world::object
	> world_;

	sanguis::collision::world::created created_;

	fcppt::reference<
		sanguis::creator::grid const
	> grid_;

	sanguis::server::center center_;

	sanguis::server::angle angle_;
};

}
}
}

#endif
