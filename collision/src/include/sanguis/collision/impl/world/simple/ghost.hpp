#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_GHOST_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_GHOST_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/impl/world/simple/body_fwd.hpp>
#include <sanguis/collision/impl/world/simple/ghost_fwd.hpp>
#include <sanguis/collision/impl/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/optional_body_enter_fwd.hpp>
#include <sanguis/collision/world/optional_body_exit_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_std_hash.hpp>
#include <fcppt/preprocessor/warn_unused_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
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
		sanguis::collision::impl::world::simple::ghost_remove_callback const &
	);

	~ghost()
	override;

	void
	center(
		sanguis::collision::center
	)
	override;

	sanguis::collision::center
	center() const
	FCPPT_PP_WARN_UNUSED_RESULT;

	sanguis::collision::radius
	radius() const
	FCPPT_PP_WARN_UNUSED_RESULT;

	sanguis::collision::world::ghost_group
	collision_group() const
	FCPPT_PP_WARN_UNUSED_RESULT;

	void
	pre_update_bodies();

	sanguis::collision::world::body_exit_container
	post_update_bodies()
	FCPPT_PP_WARN_UNUSED_RESULT;

	sanguis::collision::world::optional_body_enter
	update_near_body(
		sanguis::collision::impl::world::simple::body const &
	)
	FCPPT_PP_WARN_UNUSED_RESULT;

	sanguis::collision::world::optional_body_enter
	new_body(
		sanguis::collision::impl::world::simple::body const &,
		sanguis::collision::world::created
	)
	FCPPT_PP_WARN_UNUSED_RESULT;

	sanguis::collision::world::optional_body_exit
	remove_body(
		sanguis::collision::impl::world::simple::body const &
	)
	FCPPT_PP_WARN_UNUSED_RESULT;

	void
	body_destroyed(
		sanguis::collision::impl::world::simple::body const &
	);
private:
	sanguis::collision::impl::world::simple::ghost_remove_callback const ghost_remove_callback_;

	sanguis::collision::radius const radius_;

	sanguis::collision::world::ghost_group const collision_group_;

	sanguis::collision::center center_;

	sanguis::collision::world::ghost_base &ghost_base_;

	enum class body_status
	{
		marked_for_deletion,
		normal
	};

	typedef
	fcppt::reference<
		sanguis::collision::impl::world::simple::body const
	>
	const_body_ref;

	typedef
	std::unordered_map<
		const_body_ref,
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
