#ifndef SANGUIS_SERVER_AI_CREATE_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_SIMPLE_HPP_INCLUDED

#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/entities/auto_weak_link_fwd.hpp>
#include <sanguis/diff_clock_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

ai::create_function const
create_simple(
	sanguis::diff_clock const &,
	entities::auto_weak_link const &
);

}
}
}

#endif
