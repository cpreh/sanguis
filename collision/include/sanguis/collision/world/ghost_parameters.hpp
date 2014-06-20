#ifndef SANGUIS_COLLISION_WORLD_GHOST_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GHOST_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/group.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class ghost_parameters
{
public:
	SANGUIS_COLLISION_SYMBOL
	ghost_parameters(
		sanguis::collision::center,
		sanguis::collision::radius,
		sanguis::collision::world::body_enter_callback const &,
		sanguis::collision::world::body_exit_callback const &,
		sanguis::collision::world::group
	);

	sanguis::collision::center const
	center() const;

	sanguis::collision::radius const
	radius() const;

	sanguis::collision::world::body_enter_callback const &
	body_enter_callback() const;

	sanguis::collision::world::body_exit_callback const &
	body_exit_callback() const;

	sanguis::collision::world::group
	collision_group() const;
private:
	sanguis::collision::center center_;

	sanguis::collision::radius radius_;

	sanguis::collision::world::body_enter_callback body_enter_callback_;

	sanguis::collision::world::body_exit_callback body_exit_callback_;

	sanguis::collision::world::group collision_group_;
};

}
}
}

#endif
