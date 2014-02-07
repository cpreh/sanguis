#ifndef SANGUIS_COLLISION_AUX__WORLD_SIMPLE_BODY_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_SIMPLE_BODY_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/aux_/world/simple/body_base_hook.hpp>
#include <sanguis/collision/aux_/world/simple/body_fwd.hpp>
#include <sanguis/collision/aux_/world/simple/body_move_callback.hpp>
#include <sanguis/collision/aux_/world/simple/body_remove_callback.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/collision/world/position_change_callback.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


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

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class body
:
	public sanguis::collision::world::body,
	public sanguis::collision::aux_::world::simple::body_base_hook
{
	FCPPT_NONCOPYABLE(
		body
	);
public:
	body(
		sanguis::collision::world::body_parameters const &,
		sanguis::collision::aux_::world::simple::body_remove_callback const &,
		sanguis::collision::aux_::world::simple::body_move_callback const &
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
		sanguis::collision::center
	);

	sanguis::collision::center const
	center() const
	override;

	void
	speed(
		sanguis::collision::speed
	)
	override;

	sanguis::collision::speed const
	speed() const
	override;

	sanguis::collision::radius const
	radius() const;

	sanguis::collision::world::group_field const
	collision_groups() const;

	sanguis::collision::world::body_base &
	body_base() const;
private:
	sanguis::collision::aux_::world::simple::body_remove_callback const body_remove_callback_;

	sanguis::collision::aux_::world::simple::body_move_callback const body_move_callback_;

	sanguis::collision::world::position_change_callback const position_change_callback_;

	sanguis::collision::radius const radius_;

	sanguis::collision::world::group_field const collision_groups_;

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
