#ifndef SANGUIS_SERVER_ENTITIES_MOVABLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_MOVABLE_HPP_INCLUDED

#include "base.hpp"
#include "property.hpp"
#include "../movement_speed.hpp"
#include "../space_unit.hpp"
#include <sge/signals/scoped_connection.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class movable
:
	public virtual base
{
public:
	property &
	movement_speed();

	space_unit
	direction() const;

	void
	direction(
		space_unit
	);
protected:
	explicit movable(
		server::movement_speed max_speed
	);
private:
	property movement_speed_;

	space_unit direction_;
	
	sge::signals::scoped_connection speed_change_;
};

}
}
}

#endif

