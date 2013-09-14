#ifndef SANGUIS_COLLISION_AUX__WORLD_GROUP_PAIR_VECTOR_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_GROUP_PAIR_VECTOR_HPP_INCLUDED

#include <sanguis/collision/aux_/world/group_pair.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{

typedef
std::vector<
	sanguis::collision::aux_::world::group_pair
>
group_pair_vector;

}
}
}
}

#endif
