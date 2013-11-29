#ifndef SANGUIS_SERVER_AI_CREATE_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_FRIEND_HPP_INCLUDED

#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/sight_range_fwd.hpp>
#include <sanguis/server/entities/spawn_owner_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

sanguis::server::ai::create_function
create_friend(
	sanguis::server::ai::sight_range,
	sanguis::server::entities::spawn_owner const &
);

}
}
}

#endif
