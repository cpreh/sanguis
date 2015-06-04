#ifndef SANGUIS_SERVER_WORLD_PICKUP_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PICKUP_SPAWNER_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/random/distributor_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_decl.hpp>
#include <fcppt/random/distribution/transform/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
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
	spawn_weapon(
		sanguis::server::center,
		sanguis::server::entities::enemies::difficulty,
		sanguis::weapon_type
	);

	void
	spawn_entity(
		sanguis::server::entities::with_id_unique_ptr &&,
		sanguis::server::center
	);

	typedef
	std::function<
		void (
			sanguis::server::center,
			sanguis::server::entities::enemies::difficulty
		)
	>
	spawn_function;

	sanguis::server::world::pickup_spawner::spawn_function
	make_spawn_weapon(
		sanguis::weapon_type const &
	);

	sanguis::random_generator &random_generator_;

	sanguis::server::environment::object &env_;

	typedef
	fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			sanguis::server::pickup_probability::value_type
		>
	>
	real_distribution;

	typedef
	sanguis::server::random::distributor<
		sanguis::server::pickup_probability,
		spawn_function
	>
	distributor;

	distributor distributor_;

	real_distribution spawn_prob_;
};

}
}
}

#endif
