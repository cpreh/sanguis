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
		environment const &,
		armor_array const &,
		messages::pos_type const &center,
		messages::space_unit const direction,
		messages::space_unit const speed,
		messages::space_unit const angle,
		messages::space_unit const health,
		messages::space_unit const max_health);

	messages::dim_type dim() const;
	messages::exp_type exp() const;
	messages::space_unit max_speed() const;
	entity_type::type type() const;
	bool invulnerable() const;
};
}
}
}
#endif
