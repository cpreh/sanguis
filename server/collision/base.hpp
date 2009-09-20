#ifndef SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED

#include "shape_vector.hpp"
#include "create_parameters_fwd.hpp"
#include "../pos_type.hpp"
#include <sge/collision/world_fwd.hpp>
#include <sge/collision/body_fwd.hpp>
#include <sge/noncopyable.hpp>
#include <boost/logic/tribool_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class base {
	SGE_NONCOPYABLE(base)
protected:
	base();

	void
	body_pos(
		pos_type const &
	);

	pos_type const
	body_pos() const;

	void
	body_speed(
		pos_type const &
	);

	pos_type const
	body_speed() const;
public:
	void
	recreate(
		sge::collision::world_ptr,
		create_parameters const &
	);

	virtual shape_vector const
	recreate_shapes(
		sge::collision::world_ptr
	) const = 0;

	virtual ~base();

	virtual boost::logic::tribool const
	can_collide_with(
		collision::base const &
	) const;

	virtual void
	collision_begin(
		collision::base &
	);

	virtual void
	collision_end(
		collision::base &
	);
private:
	sge::collision::body_ptr body_;
	shape_vector shapes_;
};

}
}
}

#endif
