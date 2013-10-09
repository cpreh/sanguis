#ifndef SANGUIS_COLLISION_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_collision_callback.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>
#include <sanguis/creator/dim.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class parameters
{
public:
	SANGUIS_COLLISION_SYMBOL
	parameters(
		sanguis::collision::world::body_collision_callback const &,
		sanguis::creator::dim
	);

	sanguis::collision::world::body_collision_callback const &
	body_collision_callback() const;

	sanguis::creator::dim
	grid_size() const;
private:
	sanguis::collision::world::body_collision_callback body_collision_callback_;

	sanguis::creator::dim grid_size_;
};

}
}
}

#endif
