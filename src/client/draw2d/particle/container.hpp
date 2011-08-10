#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_CONTAINER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_CONTAINER_HPP_INCLUDED

#include "base.hpp"
#include "base_ptr.hpp"
#include "depth.hpp"
#include "rotation.hpp"
#include "rotation_speed.hpp"
#include "../center.hpp"
#include "../speed.hpp"
#include "../../../diff_clock_fwd.hpp"
#include <fcppt/noncopyable.hpp>
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
	FCPPT_NONCOPYABLE(
		container
	);
public:
	typedef boost::ptr_list<
		base
	> children_container;

	container(
		sanguis::diff_clock const &,
		draw2d::center const &,
		draw2d::speed const &,
		particle::depth,
		particle::rotation,
		particle::rotation_speed
	);

	~container();

	children_container const &
	children() const;

	children_container &
	children();

	void
	add(
		base_ptr
	);

	bool
	update(
		draw2d::center const &,
		particle::rotation,
		particle::depth
	);

	using base::center;
	using base::speed;
	using base::depth;
	using base::rot;
	using base::rot_speed;
private:
	children_container children_;
};

}
}
}
}

#endif
