#ifndef SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/log_cref.hpp>
#include <sanguis/collision/log_fwd.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/collision/world/object_ref.hpp>
#include <sanguis/creator/grid_cref.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>


namespace sanguis::server::entities
{

class transfer_parameters
{
public:
	transfer_parameters(
		sanguis::collision::log_cref,
		sanguis::collision::world::object_ref,
		sanguis::collision::world::created,
		sanguis::creator::grid_cref,
		sanguis::server::center,
		sanguis::server::angle
	);

	[[nodiscard]]
	sanguis::collision::log const &
	log() const;

	[[nodiscard]]
	sanguis::collision::world::object &
	world() const;

	[[nodiscard]]
	sanguis::collision::world::created
	created() const;

	[[nodiscard]]
	sanguis::creator::grid const &
	grid() const;

	[[nodiscard]]
	sanguis::server::center
	center() const;

	[[nodiscard]]
	sanguis::server::angle
	angle() const;
private:
	sanguis::collision::log_cref log_;

	sanguis::collision::world::object_ref world_;

	sanguis::collision::world::created created_;

	sanguis::creator::grid_cref grid_;

	sanguis::server::center center_;

	sanguis::server::angle angle_;
};

}

#endif
