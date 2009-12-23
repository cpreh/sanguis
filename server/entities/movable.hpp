#ifndef SANGUIS_SERVER_ENTITIES_MOVABLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_MOVABLE_HPP_INCLUDED

#include "movable_fwd.hpp"
#include "base.hpp"
#include "property/initial_fwd.hpp"
#include "property/changeable.hpp"
#include "property/value.hpp"
#include "../space_unit.hpp"
#include <fcppt/signal/scoped_connection.hpp>

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
	property::changeable &
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
		property::initial const &speed_,
		space_unit direction_ 
	);
private:
	pos_type const
	initial_direction() const;

	void
	speed_change(
		property::value
	);

	property::changeable movement_speed_;

	space_unit direction_;
	
	fcppt::signal::scoped_connection speed_change_;
};

}
}
}

#endif

