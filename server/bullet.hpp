#ifndef SANGUIS_SERVER_BULLET_HPP_INCLUDED
#define SANGUIS_SERVER_BULLET_HPP_INCLUDED

#include "entity.hpp"
#include <sge/console/console.hpp>

namespace sanguis
{
namespace server
{
class bullet : public entity
{
	public:
	bullet(const entity_id,const messages::pos_type &center,const messages::space_unit direction,const messages::space_unit angle);

	messages::dim_type dim() const;
	messages::space_unit max_speed() const;
	entity_type::type type() const { return entity_type::bullet; }
	ai_type::type ai_type() const { return ai_type::none; }
	void update(const time_type);
	void attack(entity &);
	bool invulnerable() const;
};
}
}

#endif
