#ifndef SANGUIS_SERVER_COLLISION_CIRCLE_GHOST_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CIRCLE_GHOST_HPP_INCLUDED

#include "ghost.hpp"
#include "ghost_parameters_fwd.hpp"
#include "body_enter_callback.hpp"
#include "body_exit_callback.hpp"
#include "../center.hpp"
#include "../radius.hpp"
#include <fcppt/function/object.hpp>
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
		server::center const &,
		server::radius,
		collision::body_enter_callback const &,
		collision::body_exit_callback const &
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

	server::radius const radius_;

	collision::body_enter_callback const body_enter_callback_;

	collision::body_exi_callback const body_exit_callback_;
};

}
}
}

#endif
