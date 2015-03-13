#ifndef SANGUIS_COLLISION_AUX__WORLD_SIMPLE_GHOST_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_SIMPLE_GHOST_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/aux_/world/simple/body_fwd.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_fwd.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/optional_body_enter_fwd.hpp>
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

	sanguis::collision::world::ghost_group
	collision_group() const;

	void
	pre_update_bodies();

	void
	post_update_bodies();

	void
	update_near_body(
		sanguis::collision::aux_::world::simple::body const &
	);

	sanguis::collision::world::optional_body_enter
	new_body(
		sanguis::collision::aux_::world::simple::body const &,
		sanguis::collision::world::created
	);

	void
	remove_body(
		sanguis::collision::aux_::world::simple::body const &
	);
private:
	sanguis::collision::aux_::world::simple::ghost_remove_callback const ghost_remove_callback_;

	sanguis::collision::radius const radius_;

	sanguis::collision::world::body_enter_callback const body_enter_callback_;

	sanguis::collision::world::body_exit_callback const body_exit_callback_;

	sanguis::collision::world::ghost_group const collision_group_;

	sanguis::collision::center center_;

	sanguis::collision::world::ghost_base &ghost_base_;

	enum class body_status
	{
		marked_for_deletion,
		normal
	};

	typedef
	std::unordered_map<
		sanguis::collision::aux_::world::simple::body const *,
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
