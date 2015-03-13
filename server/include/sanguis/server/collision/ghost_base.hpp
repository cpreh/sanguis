#ifndef SANGUIS_SERVER_COLLISION_GHOST_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_BASE_HPP_INCLUDED

#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/ghost_base.hpp>
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
:
	public sanguis::collision::world::ghost_base
{
	FCPPT_NONCOPYABLE(
		ghost_base
	);
protected:
	ghost_base();

	~ghost_base()
	override;
public:
	sanguis::collision::world::body_enter_callback
	body_enter_callback();

	sanguis::collision::world::body_exit_callback
	body_exit_callback();
private:
	virtual
	void
	body_enter(
		sanguis::collision::world::body_base &,
		sanguis::collision::world::created
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
