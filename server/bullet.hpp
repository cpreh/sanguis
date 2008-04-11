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
	messages::space_unit health() const { return static_cast<messages::space_unit>(1); }
	messages::space_unit max_health() const { return static_cast<messages::space_unit>(1); }
	entity_type::type type() const { return entity_type::bullet; }
	ai_type::type ai_type() const { return ai_type::none; }
	void update(const time_type);

	// own functions
	bool visible() const { return visible_; }

	private:
	static sge::con::var<messages::space_unit> bullet_speed;

	bool visible_;
};
}
}

#endif
