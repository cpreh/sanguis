#ifndef SANGUIS_COLLISION_SCALE_HPP_INCLUDED
#define SANGUIS_COLLISION_SCALE_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/literal.hpp>


namespace sanguis
{
namespace collision
{

inline
sanguis::collision::unit
scale()
{
	return
		fcppt::literal<
			sanguis::collision::unit
		>(
			2
		);
}

}
}

#endif
