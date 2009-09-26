#ifndef SANGUIS_SERVER_ENTITIES_MOVABLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_MOVABLE_HPP_INCLUDED

#include "movable_fwd.hpp"
#include "base.hpp"
#include "property.hpp"
#include "../movement_speed.hpp"
#include "../space_unit.hpp"
#include <sge/signal/scoped_connection.hpp>

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

	pos_type const
	abs_speed() const;
protected:
	movable(
		server::movement_speed max_speed,
		space_unit direction_ 
	);
private:
	pos_type const
	initial_direction() const;

	void
	speed_change(
		property::value_type
	);

	property movement_speed_;

	space_unit direction_;
	
	sge::signal::scoped_connection speed_change_;
};

}
}
}

#endif

