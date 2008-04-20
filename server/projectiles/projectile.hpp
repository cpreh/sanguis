#ifndef SANGUIS_SERVER_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include "../../time_type.hpp"
#include "../../messages/types.hpp"
#include "../entity.hpp"
#include <sge/timer.hpp>

namespace sanguis
{
namespace server
{
namespace projectiles
{

class projectile : public entity {
protected:
	projectile(
		messages::pos_type const& pos,
		messages::space_unit angle,
		messages::space_unit max_health,
		team::type team,
		messages::space_unit speed,
		messages::space_unit max_speed,
		time_type lifetime);
private:
	virtual bool invulnerable() const;
	void update(
		time_type,
		entity_container &entities);
	messages::space_unit max_speed() const;
	messages::dim_type dim() const;

	virtual void do_hit(entity &target) = 0;
	void die();
	virtual void do_die();

	messages::space_unit max_speed_;
	sge::timer           lifetime;
};

}
}
}

#endif
