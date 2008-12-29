#ifndef SANGUIS_DRAW_PARTICLE_CONTAINER_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_CONTAINER_HPP_INCLUDED

#include "base.hpp"
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis 
{
namespace draw
{
namespace particle
{

class container : public base
{
	public:
	typedef boost::ptr_list<base> children_container;
	explicit container(
		point const &pos,
		point const &speed,
		depth_type,
		rotation_type,
		rotation_type);
	children_container const &children() const;
	children_container &children();
	void add(base_ptr ptr);

	void gather(
		point const &,
		rotation_type,
		depth_type,
		sge::sprite::container &) const;
	bool update(time_type);

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

#endif
