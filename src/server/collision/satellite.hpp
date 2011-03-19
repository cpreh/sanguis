#ifndef SANGUIS_SERVER_COLLISION_SATELLITE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_SATELLITE_HPP_INCLUDED

#include "base_fwd.hpp"
#include <sge/collision/satellite.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class satellite
:
	public sge::collision::satellite
{
	FCPPT_NONCOPYABLE(
		satellite
	);
public:
	explicit satellite(
		collision::base &
	);

	~satellite();
	
	void
	position_change(
		sge::collision::point const &
	);
	
	void
	velocity_change(
		sge::collision::point const &
	);
	
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
