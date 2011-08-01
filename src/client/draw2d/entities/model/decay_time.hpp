#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_DECAY_TIME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_DECAY_TIME_HPP_INCLUDED

#include "decay_time_fwd.hpp"
#include "../../../../diff_clock_fwd.hpp"
#include "../../../../diff_timer.hpp"
#include "../../../../duration_fwd.hpp"
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		decay_time
	);
public:
	decay_time(
		sanguis::diff_clock const &,
		sanguis::duration const &
	);

	~decay_time();

	bool
	ended() const;
private:
	sanguis::diff_timer timer_;
};

}
}
}
}
}

#endif
