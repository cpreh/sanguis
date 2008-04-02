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
	bullet(const entity_id,const messages::pos_type &center,const messages::pos_type &direction,const messages::space_unit angle);

	// virtual functions
	messages::pos_type center() const { return center_; }
	messages::pos_type speed() const;
	messages::space_unit angle() const { return angle_; }
	messages::space_unit health() const { return static_cast<messages::space_unit>(1); }
	messages::space_unit max_health() const { return static_cast<messages::space_unit>(1); }
	entity_type::type type() const { return entity_type::bullet; }
	void update(const time_type);

	// own functions
	bool visible() const { return visible_; }

	private:
	static sge::con::var<messages::space_unit> bullet_speed;

	messages::pos_type center_,direction_;
	messages::space_unit angle_;
	bool visible_;
};
}
}

#endif
