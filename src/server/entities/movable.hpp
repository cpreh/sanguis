#ifndef SANGUIS_SERVER_ENTITIES_MOVABLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_MOVABLE_HPP_INCLUDED

#include "movable_fwd.hpp"
#include "with_body.hpp"
#include "property/initial_fwd.hpp"
#include "property/changeable.hpp"
#include "property/value.hpp"
#include "../direction.hpp"
#include "../speed.hpp"
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
	public virtual entities::with_body
{
	FCPPT_NONCOPYABLE(
		movable
	);
public:
	property::changeable &
	movement_speed();

	server::direction const
	direction() const;

	void
	direction(
		server::direction
	);

	server::speed const
	abs_speed() const;

	virtual ~movable();
protected:
	movable(
		property::initial const &speed,
		server::direction
	);
private:
	server::speed const
	initial_direction() const;

	void
	speed_change(
		property::value
	);

	property::changeable movement_speed_;

	server::direction direction_;
	
	fcppt::signal::scoped_connection const speed_change_;
};

}
}
}

#endif

