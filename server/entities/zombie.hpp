#ifndef SANGUIS_SERVER_ENTITIES_ZOMBIE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ZOMBIE_HPP_INCLUDED

#include "../entity_with_weapon.hpp"
#include "../../net/types.hpp"
#include <sge/timer.hpp>
#include <sge/console/console.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
class zombie : public entity_with_weapon
{
	public:
	zombie(
		const messages::pos_type &center,
		const messages::space_unit direction,
		const messages::space_unit speed,
		const messages::space_unit angle,
		const messages::space_unit health,
		const messages::space_unit max_health);

	messages::dim_type dim() const;
	messages::space_unit max_speed() const;
	entity_type::type type() const;
	bool invulnerable() const;
	void attack(entity &);

	private:
	sge::timer cooldown;
};
}
}
}

#endif
