#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_LIMITED_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_LIMITED_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/enemy_type_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/spawns/count_per_wave.hpp>
#include <sanguis/server/entities/spawns/hidden.hpp>
#include <sanguis/server/entities/spawns/interval.hpp>
#include <sanguis/server/entities/spawns/limit.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
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
	public sanguis::server::entities::spawns::spawn,
	public sanguis::server::entities::spawns::hidden
{
	FCPPT_NONCOPYABLE(
		limited
	);
public:
	limited(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::enemy_type,
		sanguis::server::entities::spawns::count_per_wave,
		sanguis::server::entities::spawns::interval,
		sanguis::server::entities::spawns::limit
	);

	~limited();
private:
	void
	unregister(
		sanguis::server::entities::base &
	);

	sanguis::server::entities::spawns::size_type
	may_spawn();

	void
	add_count(
		sanguis::server::entities::spawns::size_type
	);

	sanguis::server::entities::spawns::count_per_wave const count_per_wave_;

	sanguis::diff_timer delay_timer_;

	sanguis::server::entities::spawns::size_type spawned_;

	sanguis::server::entities::spawns::limit const limit_;
};

}
}
}
}

#endif
