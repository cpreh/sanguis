#ifndef SANGUIS_SERVER_COLLISION_GHOST_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_BASE_HPP_INCLUDED

#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

class ghost_base
{
	FCPPT_NONCOPYABLE(
		ghost_base
	);
protected:
	ghost_base();

	virtual
	~ghost_base() = 0;

	virtual
	boost::logic::tribool const
	can_collide_with(
		sanguis::collision::world::body_base const &
	) const = 0;

	sanguis::collision::world::body_enter_callback
	body_enter_callback();

	sanguis::collision::world::body_exit_callback
	body_exit_callback();
private:
	void
	collision_begin(
		sanguis::collision::world::body_base &
	);

	void
	collision_end(
		sanguis::collision::world::body_base &
	);

	virtual
	void
	body_enter(
		sanguis::collision::world::body_base &
	) = 0;

	virtual
	void
	body_exit(
		sanguis::collision::world::body_base &
	) = 0;
};

}
}
}

#endif
