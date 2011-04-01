#ifndef SANGUIS_SERVER_COLLISION_CIRCLE_GHOST_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CIRCLE_GHOST_HPP_INCLUDED

#include "ghost.hpp"
#include "ghost_parameters_fwd.hpp"
#include "../space_unit.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class circle_ghost
:
	public collision::ghost
{
	FCPPT_NONCOPYABLE(
		circle_ghost
	);
protected:
	circle_ghost(
		collision::ghost_parameters const &,
		server::pos const &center,
		server::space_unit radius
	);
public:
	virtual ~circle_ghost();
private:
	void
	on_body_enter(
		sge::projectile::body::object const &
	);

	void
	on_body_exit(
		sge::projectile::body::object const &
	);

	server::space_unit const radius_;
};

}
}
}

#endif
