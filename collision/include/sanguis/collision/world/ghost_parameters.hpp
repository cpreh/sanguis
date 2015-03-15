#ifndef SANGUIS_COLLISION_WORLD_GHOST_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GHOST_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class ghost_parameters
{
	FCPPT_NONASSIGNABLE(
		ghost_parameters
	);
public:
	SANGUIS_COLLISION_SYMBOL
	ghost_parameters(
		sanguis::collision::center,
		sanguis::collision::radius,
		sanguis::collision::world::ghost_group,
		sanguis::collision::world::ghost_base &
	);

	sanguis::collision::center const
	center() const;

	sanguis::collision::radius const
	radius() const;

	sanguis::collision::world::ghost_group
	collision_group() const;

	sanguis::collision::world::ghost_base &
	ghost_base() const;
private:
	sanguis::collision::center const center_;

	sanguis::collision::radius const radius_;

	sanguis::collision::world::ghost_group const collision_group_;

	sanguis::collision::world::ghost_base &ghost_base_;
};

}
}
}

#endif
