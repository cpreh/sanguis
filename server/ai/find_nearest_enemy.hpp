#ifndef SANGUIS_SERVER_AI_FIND_NEAREST_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_AI_FIND_NEAREST_ENEMY_HPP_INCLUDED

#include "../pos_type.hpp"
#include "../entities/auto_weak_link_fwd.hpp"
#include "../entities/entity_fwd.hpp"
#include "../entities/container.hpp"

namespace sanguis
{
namespace server
{
namespace ai
{

entities::auto_weak_link
find_nearest_enemy(
	entities::entity &me,
	pos_type const &pos,
	entities::container &);

}
}
}


#endif
