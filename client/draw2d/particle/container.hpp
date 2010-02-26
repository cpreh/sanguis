#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_CONTAINER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_CONTAINER_HPP_INCLUDED

#include "base.hpp"
#include "base_ptr.hpp"
#include "time_type.hpp"
#include "point.hpp"
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis 
{
namespace client
{
namespace draw2d
{
namespace particle
{

class container
:
	public base
{
public:
	typedef boost::ptr_list<
		base
	> children_container;

	container(
		point const &pos,
		point const &speed,
		depth_type,
		rotation_type,
		rotation_type
	);

	children_container const &
	children() const;

	children_container &
	children();

	void
	add(
		base_ptr ptr
	);

	bool
	update(
		time_type,
		point const &,
		rotation_type,
		depth_type
	);

	using base::pos;
	using base::vel;
	using base::depth;
	using base::rot;
	using base::rot_vel;
private:
	children_container children_;
};

}
}
}
}

#endif
