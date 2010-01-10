#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_DECAY_TIME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_DECAY_TIME_HPP_INCLUDED

#include "decay_time_fwd.hpp"
#include "../../../../diff_clock.hpp"
#include <sge/time/timer.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

class decay_time
{
public:
	decay_time();

	void
	update(
		time_type
	);

	bool
	ended() const;
private:
	diff_clock diff_clock_;
	
	sge::time::timer timer_;
};

}
}
}
}
}

#endif
