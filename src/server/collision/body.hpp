#ifndef SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED

#include "body_fwd.hpp"
#include "global_groups_fwd.hpp"
#include "create_parameters_fwd.hpp"
#include "../pos_type.hpp"
#include <sge/collision/shapes/container.hpp>
#include <sge/collision/world_ptr.hpp>
#include <sge/collision/body_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class body
{
	FCPPT_NONCOPYABLE(
		body
	);
protected:
	body();

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

	void
	add_shapes(
		sge::collision::shapes::container const &
	);
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
		sge::collision::world_ptr,
		global_groups const &
	) = 0;

	virtual ~body();
private:
	virtual void
	on_destroy();

	sge::collision::body_ptr body_;
	
	sge::collision::shapes::container shapes_;
};

}
}
}

#endif

