#ifndef SANGUIS_SERVER_WORLD_PICKUP_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PICKUP_SPAWNER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <vector>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class pickup_spawner
{
	FCPPT_NONCOPYABLE(
		pickup_spawner
	);
public:
	pickup_spawner(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::server::environment::object &
	);

	~pickup_spawner();

	void
	spawn(
		sanguis::server::pickup_probability,
		sanguis::server::center,
		sanguis::server::entities::enemies::difficulty
	);
private:
	void
	spawn_health(
		sanguis::server::center,
		sanguis::server::entities::enemies::difficulty
	);

	void
	spawn_monster(
		sanguis::server::center,
		sanguis::server::entities::enemies::difficulty
	);

	void
	spawn_weapon(
		sanguis::server::center,
		sanguis::server::entities::enemies::difficulty,
		sanguis::weapon_type
	);

	void
	spawn_entity(
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::center
	);

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::server::environment::object &env_;

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			sanguis::server::pickup_probability::value_type
		>
	> real_distribution;

	typedef fcppt::random::variate<
		sanguis::random_generator,
		real_distribution
	> real_variate;

	typedef std::function<
		void (
			sanguis::server::center,
			sanguis::server::entities::enemies::difficulty
		)
	> spawn_function;

	typedef std::pair<
		sanguis::server::pickup_probability,
		spawn_function
	> spawn_pair;

	typedef std::vector<
		spawn_pair
	> spawn_vector;

	spawn_vector const spawns_;

	real_variate
		spawn_prob_,
		spawn_value_;
};

}
}
}

#endif
