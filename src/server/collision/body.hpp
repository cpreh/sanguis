#ifndef SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED

#include "body_fwd.hpp"
#include "global_groups_fwd.hpp"
#include "create_parameters_fwd.hpp"
#include "../pos.hpp"
#include <sge/projectile/shapes/base_ptr.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

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
		server::pos const &
	);

	server::pos const
	body_pos() const;

	void
	body_speed(
		server::pos const &
	);

	server::pos const
	body_speed() const;
public:
	void
	recreate(
		sge::projectile::world &,
		collision::global_groups const &,
		collision::create_parameters const &
	);

	void
	destroy();

	virtual ~body();
private:
	virtual sge::projectile::shapes::base_ptr const
	recreate_shape(
		sge::collision::world &,
		collision::global_groups const &
	) = 0;

	virtual void
	on_destroy();

	typedef fcppt::scoped_ptr<
		sge::projectile::body
	> body_scoped_ptr;

	body_scoped_ptr body_;
};

}
}
}

#endif

