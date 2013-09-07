#ifndef SANGUIS_COLLISION_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_collision_callback.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>


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
	explicit
	parameters(
		sanguis::collision::world::body_collision_callback const &
	);

	sanguis::collision::world::body_collision_callback const &
	body_collision_callback() const;
private:
	sanguis::collision::world::body_collision_callback body_collision_callback_;
};

}
}
}

#endif
