#ifndef SANGUIS_SERVER_PICKUP_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_PICKUP_SPAWNER_HPP_INCLUDED

#include "environment/object_fwd.hpp"
#include "center.hpp"
#include "probability.hpp"
#include "../diff_clock_fwd.hpp"
#include "../weapon_type.hpp"
#include <fcppt/random/actor/normalized.hpp>
#include <fcppt/random/uniform.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>

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
	spawn_health();

	void
	spawn_monster();

	void
	spawn_weapon(
		weapon_type::type
	);

	sanguis::diff_clock const &diff_clock_;
	
	environment::object &env_;

	fcppt::random::uniform<
		server::probability::value_type
	> spawn_prob_;

	fcppt::random::actor::normalized rng_;

	server::center center_;
};

}
}

#endif
