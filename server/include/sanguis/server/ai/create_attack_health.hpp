#ifndef SANGUIS_SERVER_AI_CREATE_ATTACK_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_ATTACK_HEALTH_HPP_INCLUDED

#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/sight_range_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

sanguis::server::ai::create_function
create_attack_health(
	sanguis::random_generator_ref,
	sanguis::server::ai::sight_range
);

}
}
}

#endif
