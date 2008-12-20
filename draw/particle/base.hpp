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
	explicit base(
		point const &,
		point const &,
		depth_type,
		rotation_type,
		rotation_type);
	public:
	virtual bool update(time_type);
	virtual void pos(point const &p) { pos_ = p; }
	virtual void vel(point const &p) { vel_ = p; }
	virtual void depth(depth_type const p) { depth_ = p; }
	virtual void rot(rotation_type const p) { rot_ = p; }
	virtual void rot_vel(rotation_type const p) { rot_vel_ = p; }
	virtual void gather(
		point const &,
		rotation_type,
		depth_type,
		sge::sprite::system::container &) const = 0;
	point const &pos() const { return pos_; }
	point &pos() { return pos_; }
	point const &vel() const { return vel_; }
	point &vel() { return vel_; }
	depth_type const &depth() const { return depth_; }
	depth_type &depth() { return depth_; }
	rotation_type const &rot() const { return rot_; }
	rotation_type &rot() { return rot_; }
	rotation_type const &rot_vel() const { return rot_vel_; }
	rotation_type &rot_vel() { return rot_vel_; }
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
