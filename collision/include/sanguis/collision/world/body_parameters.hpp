#ifndef SANGUIS_COLLISION_WORLD_BODY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/group_vector.hpp>
#include <sanguis/collision/world/position_change_callback.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class body_parameters
{
	FCPPT_NONASSIGNABLE(
		body_parameters
	);
public:
	SANGUIS_COLLISION_SYMBOL
	body_parameters(
		sanguis::collision::center,
		sanguis::collision::speed,
		sanguis::collision::radius,
		sanguis::collision::world::position_change_callback const &,
		sanguis::collision::world::group_vector const &,
		sanguis::collision::world::body_base &
	);

	sanguis::collision::center const
	center() const;

	sanguis::collision::speed const
	speed() const;

	sanguis::collision::radius const
	radius() const;

	sanguis::collision::world::position_change_callback const &
	position_change_callback() const;

	sanguis::collision::world::group_vector const &
	collision_groups() const;

	sanguis::collision::world::body_base &
	body_base() const;
private:
	sanguis::collision::center const center_;

	sanguis::collision::speed const speed_;

	sanguis::collision::radius const radius_;

	sanguis::collision::world::position_change_callback const position_change_callback_;

	sanguis::collision::world::group_vector const collision_groups_;

	sanguis::collision::world::body_base &body_base_;
};

}
}
}

#endif
