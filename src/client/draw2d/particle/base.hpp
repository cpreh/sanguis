#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_BASE_HPP_INCLUDED

#include "depth.hpp"
#include "rotation.hpp"
#include "rotation_speed.hpp"
#include "../center.hpp"
#include "../speed.hpp"
#include "../../../time_delta_fwd.hpp"
#include <fcppt/math/vector/basic_decl.hpp>
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
		draw2d::center const &,
		draw2d::speed const &,
		particle::depth,
		particle::rotation,
		particle::rotation_speed
	);
public:
	virtual ~base();

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
		sanguis::time_delta const &,
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
};

}
}
}
}

#endif
