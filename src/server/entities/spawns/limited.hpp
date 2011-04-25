#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_LIMITED_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_LIMITED_HPP_INCLUDED

#include "count_per_wave.hpp"
#include "hidden.hpp"
#include "interval.hpp"
#include "limit.hpp"
#include "spawn.hpp"
#include "../../../diff_clock.hpp"
#include "../../../enemy_type.hpp"
#include "../../../time_delta_fwd.hpp"
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
	FCPPT_NONCOPYABLE(
		limited
	);
public:
	explicit limited(
		enemy_type::type,
		count_per_wave,
		interval,
		limit
	);

	~limited();
private:
	void
	unregister(
		entities::base &
	);

	size_type
	may_spawn(
		sanguis::time_delta const &
	);

	void
	add_count(
		size_type
	);

	diff_clock diff_clock_;

	count_per_wave const count_per_wave_;

	sge::time::timer delay_;

	size_type spawned_;

	limit const limit_;
};

}
}
}
}

#endif
