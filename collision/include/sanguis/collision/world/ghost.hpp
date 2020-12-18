#ifndef SANGUIS_COLLISION_WORLD_GHOST_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GHOST_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/world/ghost_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class ghost
{
	FCPPT_NONMOVABLE(
		ghost
	);
protected:
	ghost();
public:
	virtual
	~ghost();

	virtual
	void
	center(
		sanguis::collision::center
	) = 0;
};

}
}
}

#endif
