#ifndef SANGUIS_SERVER_COLLISION_GHOST_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_HPP_INCLUDED

#include "ghost_fwd.hpp"
#include "body_base_fwd.hpp"
#include "ghost_parameters_fwd.hpp"
#include "../center.hpp"
#include "../dim.hpp"
#include "../pos.hpp"
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/ghost/object_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class ghost
{
	FCPPT_NONCOPYABLE(
		ghost
	);
protected:
	ghost(
		collision::ghost_parameters const &,
		server::pos const &,
		server::dim const &
	);
public:
	virtual ~ghost();

	void
	center(
		server::center const &
	);
private:
	void
	body_enter(
		sge::projectile::body::object const &
	);

	void
	body_exit(
		sge::projectile::body::object const &
	);

	virtual void
	on_body_enter(
		collision::body_base &
	) = 0;

	virtual void
	on_body_exit(
		collision::body_base &
	) = 0;

	typedef fcppt::scoped_ptr<
		sge::projectile::ghost::object
	> ghost_scoped_ptr;

	ghost_scoped_ptr ghost_;

	fcppt::signal::scoped_connection const
		collision_begin_connection_,
		collision_end_connection_;
};

}
}
}

#endif
