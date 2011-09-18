#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_LIMITED_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_LIMITED_HPP_INCLUDED

#include <sanguis/server/entities/spawns/count_per_wave.hpp>
#include <sanguis/server/entities/spawns/hidden.hpp>
#include <sanguis/server/entities/spawns/interval.hpp>
#include <sanguis/server/entities/spawns/limit.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/enemy_type.hpp>
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
	limited(
		sanguis::diff_clock const &,
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
	may_spawn();

	void
	add_count(
		size_type
	);

	count_per_wave const count_per_wave_;

	sanguis::diff_timer delay_timer_;

	size_type spawned_;

	limit const limit_;
};

}
}
}
}

#endif
