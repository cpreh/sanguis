#ifndef SANGUIS_SERVER_COLLISION_CIRCLE_GHOST_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CIRCLE_GHOST_HPP_INCLUDED

#include <sanguis/server/collision/body_base_fwd.hpp>
#include <sanguis/server/collision/body_enter_callback.hpp>
#include <sanguis/server/collision/body_exit_callback.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/radius.hpp>
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
public:
	circle_ghost(
		collision::group_vector const &,
		server::radius,
		collision::body_enter_callback const &,
		collision::body_exit_callback const &
	);

	~circle_ghost();
private:
	void
	on_body_enter(
		collision::body_base &
	);

	void
	on_body_exit(
		collision::body_base &
	);

	server::radius const radius_;

	collision::body_enter_callback const body_enter_callback_;

	collision::body_exit_callback const body_exit_callback_;
};

}
}
}

#endif
