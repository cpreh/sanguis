#ifndef SANGUIS_COLLISION_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	SANGUIS_COLLISION_SYMBOL
	explicit
	parameters(
		sanguis::creator::grid const &
	);

	sanguis::creator::grid const &
	grid() const;
private:
	sanguis::creator::grid const &grid_;
};

}
}
}

#endif
