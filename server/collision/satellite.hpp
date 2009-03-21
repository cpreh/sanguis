#ifndef SANGUIS_SERVER_COLLISION_SATELLITE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_SATELLITE_HPP_INCLUDED

#include <sge/collision/satellite.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class base;

class satellite : public sge::collision::satellite {
public:
	explicit satellite(
		collision::base &);
	
	void
	position_change(
		sge::collision::point const &);
	
	collision::base &
	base();

	collision::base const &
	base() const;
private:
	collision::base &base_;
};

}
}
}

#endif
