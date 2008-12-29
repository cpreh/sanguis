#ifndef SANGUIS_DRAW_PARTICLE_BASE_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_BASE_HPP_INCLUDED

#include "types.hpp"
#include "fwd.hpp"
#include <sge/sprite/system.hpp>

namespace sanguis
{
namespace draw
{
namespace particle
{

class base
{
	public:
	typedef particle::depth depth_type;
	typedef particle::rotation rotation_type;
	protected:
	base(
		point const &,
		point const &,
		depth_type,
		rotation_type,
		rotation_type);
	public:
	virtual ~base();
	virtual bool update(time_type);
	virtual void pos(point const &);
	virtual void vel(point const &);
	virtual void depth(depth_type);
	virtual void rot(rotation_type);
	virtual void rot_vel(rotation_type);
	virtual void gather(
		point const &,
		rotation_type,
		depth_type,
		sge::sprite::system::container &) const = 0;
	point const &pos() const;
	point &pos();
	point const &vel() const;
	point &vel();
	depth_type const &depth() const;
	depth_type &depth();
	rotation_type const &rot() const;
	rotation_type &rot();
	rotation_type const &rot_vel() const;
	rotation_type &rot_vel();
	private:
	point pos_;
	point vel_;
	depth_type depth_;
	rotation_type rot_;
	rotation_type rot_vel_;
};

}
}
}

#endif
