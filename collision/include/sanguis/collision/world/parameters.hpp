#ifndef SANGUIS_COLLISION_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
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
	explicit
	parameters(
		sanguis::creator::dim
	);

	sanguis::creator::dim
	grid_size() const;
private:
	sanguis::creator::dim grid_size_;
};

}
}
}

#endif
