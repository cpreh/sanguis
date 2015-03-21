#ifndef SANGUIS_SERVER_ENTITIES_INSERT_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_INSERT_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/world/created.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class insert_parameters
{
public:
	insert_parameters(
		sanguis::server::center,
		sanguis::server::angle
	);

	insert_parameters(
		sanguis::server::center,
		sanguis::server::angle,
		sanguis::collision::world::created
	);

	sanguis::server::center const
	center() const;

	server::angle const
	angle() const;

	sanguis::collision::world::created const
	created() const;
private:
	sanguis::server::center center_;

	sanguis::server::angle angle_;

	sanguis::collision::world::created created_;
};

}
}
}

#endif
