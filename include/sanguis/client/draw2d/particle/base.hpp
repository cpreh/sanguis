#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_BASE_HPP_INCLUDED

#include <sanguis/client/draw2d/particle/depth.hpp>
#include <sanguis/client/draw2d/particle/rotation.hpp>
#include <sanguis/client/draw2d/particle/rotation_speed.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <fcppt/math/vector/object_decl.hpp>
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base(
		sanguis::diff_clock const &,
		draw2d::center const &,
		draw2d::speed const &,
		particle::depth,
		particle::rotation,
		particle::rotation_speed
	);
public:
	virtual ~base() = 0;

	virtual void
	center(
		draw2d::center const &
	);

	virtual void
	speed(
		draw2d::speed const &
	);

	virtual void
	depth(
		particle::depth
	);

	virtual void
	rot(
		particle::rotation
	);

	virtual void
	rot_speed(
		particle::rotation_speed
	);

	virtual bool
	update(
		draw2d::center const &,
		particle::rotation,
		particle::depth
	);

	draw2d::center const &
	center() const;

	draw2d::speed const &
	speed() const;

	particle::depth const &
	depth() const;

	particle::rotation const &
	rot() const;

	particle::rotation_speed const &
	rot_speed() const;
private:
	draw2d::center center_;

	draw2d::speed speed_;

	particle::depth depth_;

	particle::rotation rot_;

	particle::rotation_speed rot_speed_;

	sanguis::diff_timer diff_timer_;
};

}
}
}
}

#endif
