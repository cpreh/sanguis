#ifndef SANGUIS_SERVER_ENTITIES_BODY_VELOCITY_COMBINER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BODY_VELOCITY_COMBINER_HPP_INCLUDED

#include "ifaces/with_body.hpp"
#include "ifaces/with_velocity.hpp"
#include "../speed.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class body_velocity_combiner
:
	public virtual ifaces::with_body,
	public virtual ifaces::with_velocity
{
	FCPPT_NONCOPYABLE(
		body_velocity_combiner
	);
public:
	body_velocity_combiner();

	~body_velocity_combiner();
private:
	void
	on_speed_change(
		server::speed const &
	);
};

}
}
}

#endif
