#ifndef SANGUIS_SERVER_PICKUP_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_PICKUP_SPAWNER_HPP_INCLUDED

#include "environment.hpp"
#include "../weapon_type.hpp"
#include <sge/random/actor/normalized.hpp>
#include <sge/math/vector/basic_decl.hpp>

namespace sanguis
{
namespace server
{

class pickup_spawner {
public:
	explicit pickup_spawner(
		environment const &);
	
	void spawn(
		pos_type const &pos);
private:
	void spawn_health();
	void spawn_monster();

	void spawn_weapon(
		weapon_type::type);
	
	environment const env;
	sge::random::actor::normalized rng;
	pos_type pos;
};

}
}

#endif
