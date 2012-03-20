#ifndef SANGUIS_SERVER_PICKUP_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_PICKUP_SPAWNER_HPP_INCLUDED

#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/probability.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/distribution/uniform_real_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
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
		environment::object &
	);

	~pickup_spawner();

	void
	spawn(
		server::probability,
		server::center const &
	);
private:
	void
	spawn_health(
		server::center const &
	);

	void
	spawn_monster(
		server::center const &
	);

	void
	spawn_weapon(
		server::center const &,
		weapon_type::type
	);

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	environment::object &env_;

	typedef fcppt::random::distribution::uniform_real<
		server::probability::value_type
	> real_distribution;

	typedef fcppt::random::variate<
		sanguis::random_generator,
		real_distribution
	> real_variate;

	typedef fcppt::function::object<
		void (
			server::center const &
		)
	> spawn_function;

	typedef std::pair<
		server::probability,
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

#endif
