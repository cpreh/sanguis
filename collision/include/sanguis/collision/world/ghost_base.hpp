#ifndef SANGUIS_COLLISION_WORLD_GHOST_BASE_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GHOST_BASE_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/symbol/class.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

class FCPPT_SYMBOL_CLASS ghost_base
{
	FCPPT_NONCOPYABLE(
		ghost_base
	);
protected:
	SANGUIS_COLLISION_SYMBOL
	ghost_base();
public:
	SANGUIS_COLLISION_SYMBOL
	virtual
	~ghost_base();
};

}
}
}

#endif
