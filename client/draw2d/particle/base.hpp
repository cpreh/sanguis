#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_BASE_HPP_INCLUDED

#include "types.hpp"
#include "fwd.hpp"
#include <fcppt/math/vector/basic_decl.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
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
		rotation_type
	);
public:
	virtual ~base();

	virtual void
	pos(
		point const &
	);

	virtual void
	vel(
		point const &
	);

	virtual void
	depth(
		depth_type
	);

	virtual void
	rot(
		rotation_type
	);

	virtual void
	rot_vel(
		rotation_type
	);

	virtual bool
	update(
		time_type,
		point const &,
		rotation_type,
		depth_type
	);

	point const &
	pos() const;

	point &
	pos();

	point const &
	vel() const;

	point &
	vel();

	depth_type const &
	depth() const;

	depth_type &
	depth();

	rotation_type const &
	rot() const;

	rotation_type &
	rot();

	rotation_type const &
	rot_vel() const;

	rotation_type &
	rot_vel();
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
}

#endif
