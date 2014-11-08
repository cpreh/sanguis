#ifndef SANGUIS_SERVER_AI_CREATE_BOSS_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_BOSS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/sight_range_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

sanguis::server::ai::create_function
create_boss(
	sanguis::random_generator &,
	sanguis::server::ai::sight_range
);

}
}
}

#endif
