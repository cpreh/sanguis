#ifndef SANGUIS_COLLISION_AUX__WORLD_SIMPLE_GHOST_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_SIMPLE_GHOST_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/aux_/world/simple/body_fwd.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_fwd.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{
namespace simple
{

class ghost
:
	public sanguis::collision::world::ghost
{
	FCPPT_NONCOPYABLE(
		ghost
	);
public:
	ghost(
		sanguis::collision::world::ghost_parameters const &,
		sanguis::collision::aux_::world::simple::ghost_remove_callback const &
	);

	~ghost()
	override;

	void
	center(
		sanguis::collision::center
	)
	override;

	sanguis::collision::center const
	center() const;

	sanguis::collision::radius const
	radius() const;

	sanguis::collision::world::group_field const
	collision_groups() const;

	void
	pre_update_bodies();

	void
	post_update_bodies();

	void
	update_near_body(
		sanguis::collision::aux_::world::simple::body &
	);

	void
	new_body(
		sanguis::collision::aux_::world::simple::body &
	);

	void
	remove_body(
		sanguis::collision::aux_::world::simple::body &
	);
private:
	sanguis::collision::aux_::world::simple::ghost_remove_callback const ghost_remove_callback_;

	sanguis::collision::radius const radius_;

	sanguis::collision::world::body_enter_callback const body_enter_callback_;

	sanguis::collision::world::body_exit_callback const body_exit_callback_;

	sanguis::collision::world::group_field const collision_groups_;

	sanguis::collision::center center_;

	enum class body_status
	{
		marked_for_deletion,
		normal
	};

	typedef
	std::unordered_map<
		sanguis::collision::aux_::world::simple::body *,
		body_status
	>
	body_map;

	body_map bodies_;
};

}
}
}
}
}

#endif
