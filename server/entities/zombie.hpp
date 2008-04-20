#ifndef SANGUIS_SERVER_ENTITIES_ZOMBIE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ZOMBIE_HPP_INCLUDED

#include "enemy.hpp"
#include "../../net/types.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
class zombie : public enemy
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
};
}
}
}
#endif
