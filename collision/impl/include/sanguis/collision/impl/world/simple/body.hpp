#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/optional_mass.hpp>
#include <sanguis/collision/optional_result_fwd.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/result_fwd.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/impl/world/simple/body_base_hook.hpp>
#include <sanguis/collision/impl/world/simple/body_fwd.hpp>
#include <sanguis/collision/impl/world/simple/body_move_callback.hpp>
#include <sanguis/collision/impl/world/simple/body_remove_callback.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


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

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)
FCPPT_PP_DISABLE_GCC_WARNING(-Wnon-virtual-dtor)

class body
:
	public sanguis::collision::world::body,
	public sanguis::collision::impl::world::simple::body_base_hook
{
	FCPPT_NONCOPYABLE(
		body
	);
public:
	body(
		sanguis::collision::world::body_parameters const &,
		sanguis::collision::impl::world::simple::body_remove_callback const &,
		sanguis::collision::impl::world::simple::body_move_callback const &
	);

	~body()
	override;

	void
	center(
		sanguis::collision::center
	)
	override;

	void
	move(
		sanguis::collision::optional_result const &,
		sanguis::collision::duration
	);

	void
	push(
		sanguis::collision::result const &
	);

	sanguis::collision::center
	center() const
	override;

	void
	speed(
		sanguis::collision::speed
	)
	override;

	sanguis::collision::speed
	speed() const
	override;

	sanguis::collision::radius
	radius() const
	override;

	sanguis::collision::optional_mass
	mass() const
	override;

	sanguis::collision::world::body_group
	collision_group() const;

	sanguis::collision::world::body_base &
	body_base() const;
private:
	void
	speed_changed();

	sanguis::collision::impl::world::simple::body_remove_callback const body_remove_callback_;

	sanguis::collision::impl::world::simple::body_move_callback const body_move_callback_;

	sanguis::collision::radius const radius_;

	sanguis::collision::optional_mass const mass_;

	sanguis::collision::world::body_group const collision_group_;

	sanguis::collision::world::body_base &body_base_;

	sanguis::collision::center center_;

	sanguis::collision::speed speed_;
};

FCPPT_PP_POP_WARNING

}
}
}
}
}

#endif
