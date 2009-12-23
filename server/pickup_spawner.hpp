#ifndef SANGUIS_SERVER_PICKUP_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_PICKUP_SPAWNER_HPP_INCLUDED

#include "environment/object_ptr.hpp"
#include "pos_type.hpp"
#include "probability_type.hpp"
#include "../weapon_type.hpp"
#include <sge/random/actor/normalized.hpp>
#include <sge/random/uniform.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{

class pickup_spawner {
	FCPPT_NONCOPYABLE(pickup_spawner)
public:
	explicit pickup_spawner(
		environment::object_ptr
	);
	
	~pickup_spawner();
	
	void
	spawn(
		probability_type,
		pos_type const &pos
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
	
	environment::object_ptr const env;

	sge::random::uniform<
		probability_type
	> spawn_prob;

	sge::random::actor::normalized rng;

	pos_type pos;
};

}
}

#endif
