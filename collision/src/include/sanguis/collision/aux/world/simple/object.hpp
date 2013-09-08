#ifndef SANGUIS_COLLISION_AUX_WORLD_SIMPLE_OBJECT_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_WORLD_SIMPLE_OBJECT_HPP_INCLUDED

#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/aux/world/simple/body_fwd.hpp>
#include <sanguis/collision/aux/world/simple/ghost_fwd.hpp>
#include <sanguis/collision/world/body_collision_callback.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{
namespace world
{
namespace simple
{

class object
:
	public sanguis::collision::world::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sanguis::collision::world::parameters const &
	);

	~object()
	override;
private:
	sanguis::collision::world::body_unique_ptr
	create_body(
		sanguis::collision::world::body_parameters const &
	)
	override;

	void
	activate_body(
		sanguis::collision::world::body &
	)
	override;

	sanguis::collision::world::ghost_unique_ptr
	create_ghost(
		sanguis::collision::world::ghost_parameters const &
	)
	override;

	void
	update(
		sanguis::collision::duration
	)
	override;

	void
	remove_body(
		sanguis::collision::aux::world::simple::body &
	);

	void
	remove_ghost(
		sanguis::collision::aux::world::simple::ghost &
	);

	sanguis::collision::world::body_collision_callback const body_collision_callback_;

	typedef
	std::unordered_set<
		sanguis::collision::aux::world::simple::body *
	>
	body_set;

	body_set bodies_;

	typedef
	std::unordered_set<
		sanguis::collision::aux::world::simple::ghost *
	>
	ghost_set;

	ghost_set ghosts_;
};

}
}
}
}
}

#endif
