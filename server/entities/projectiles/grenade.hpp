#ifndef SANGUIS_SERVER_ENTITIES_PROJECTLES_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTLES_GRENADE_HPP_INCLUDED

#include "projectile.hpp"
#include "../../../diff_clock.hpp"
#include <sge/time/timer.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class grenade : public projectile {
public:
	grenade(
		server::environment const &,
		pos_type const &center,
		space_unit angle,
		team::type,
		space_unit damage,
		space_unit aoe);
private:
	void
	do_damage(
		entity &);
	
	void
	update(
		time_type,
		container &);
	
	void on_die();
	
	diff_clock diff_clock_;
	sge::time::timer slowdown_time;
	space_unit const
		damage,
		aoe;
};

}
}
}
}

#endif
