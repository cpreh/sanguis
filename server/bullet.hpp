#ifndef SANGUIS_SERVER_BULLET_HPP_INCLUDED
#define SANGUIS_SERVER_BULLET_HPP_INCLUDED

#include "entity.hpp"

namespace sanguis
{
namespace server
{
class bullet : public entity
{
	public:
	messages::pos_type center() const { return center_; }
	messages::pos_type speed() const { return speed_; }
	messages::space_unit angle() const { return angle_; }
	messages::space_unit health() const { return static_cast<messages::space_unit>(1); }
	void update(const time_type);
	bool visible() const;
	private:
	messages::pos_type center_,speed_;
	messages::space_unit angle_;
	bool visible_;
};
}
}

#endif
