#ifndef SANGUIS_SERVER_ENTITIES_MOVABLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_MOVABLE_HPP_INCLUDED

#include "movable_fwd.hpp"
#include "base.hpp"
#include "property/initial_fwd.hpp"
#include "property/changeable.hpp"
#include "property/value.hpp"
#include "../space_unit.hpp"
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class movable
:
	public entities::with_body
{
	FCPPT_NONCOPYABLE(
		movable
	);
public:
	property::changeable &
	movement_speed();

	server::space_unit
	direction() const;

	void
	direction(
		server::space_unit
	);

	server::pos const
	abs_speed() const;
protected:
	movable(
		property::initial const &speed,
		space_unit direction
	);
private:
	server::pos const
	initial_direction() const;

	void
	speed_change(
		property::value
	);

	property::changeable movement_speed_;

	server::space_unit direction_;
	
	fcppt::signal::scoped_connection const speed_change_;
};

}
}
}

#endif

