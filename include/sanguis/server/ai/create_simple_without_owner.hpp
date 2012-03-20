#ifndef SANGUIS_SERVER_AI_CREATE_SIMPLE_WITHOUT_OWNER_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_SIMPLE_WITHOUT_OWNER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

ai::create_function const
create_simple_without_owner(
	sanguis::diff_clock const &,
	sanguis::random_generator &
);

}
}
}

#endif
