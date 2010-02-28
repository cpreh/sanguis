#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_LIMITED_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_LIMITED_HPP_INCLUDED

#include "count.hpp"
#include "delay.hpp"
#include "hidden.hpp"
#include "limit.hpp"
#include "spawn.hpp"
#include "../../../diff_clock.hpp"
#include "../../../enemy_type.hpp"
#include <sge/time/timer.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace spawns
{

class limited
:
	public spawn,
	public hidden
{
	FCPPT_NONCOPYABLE(limited)
public:
	explicit limited(
		enemy_type::type,
		count,
		delay,
		limit
	);
private:
	void
	unregister(
		entities::base &
	);

	count const
	may_spawn(
		time_type
	);

	diff_clock diff_clock_;

	count const count_;

	sge::time::timer delay_;

	count spawned_;

	limit const limit_;
};

}
}
}
}

#endif
