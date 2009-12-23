#ifndef SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BASE_HPP_INCLUDED

#include "group_vector.hpp"
#include "create_parameters_fwd.hpp"
#include "global_groups_fwd.hpp"
#include "../pos_type.hpp"
#include <sge/collision/shapes/container.hpp>
#include <sge/collision/world_fwd.hpp>
#include <sge/collision/body_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/logic/tribool_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class base {
	FCPPT_NONCOPYABLE(base)
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
		global_groups const &,
		create_parameters const &
	);

	void
	destroy();

	virtual sge::collision::shapes::container const
	recreate_shapes(
		sge::collision::world_ptr
	) const = 0;

	virtual group_vector const
	collision_groups() const = 0;

	virtual ~base();

	virtual boost::logic::tribool const
	can_collide_with(
		collision::base const &
	) const;

	virtual void
	collision_begin(
		collision::base &
	) = 0;

	virtual void
	collision_end(
		collision::base &
	) = 0;
private:
	virtual void
	on_destroy();

	sge::collision::body_ptr body_;
	group_vector const groups_;
};

}
}
}

#endif
