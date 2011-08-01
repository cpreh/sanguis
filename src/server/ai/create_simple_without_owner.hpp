#ifndef SANGUIS_SERVER_AI_CREATE_SIMPLE_WITHOUT_OWNER_HPP_INCLUDED
#define SANGUIS_SERVER_AI_CREATE_SIMPLE_WITHOUT_OWNER_HPP_INCLUDED

#include "create_function.hpp"
#include "../../diff_clock_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace ai
{

ai::create_function const
create_simple_without_owner(
	sanguis::diff_clock const &
);

}
}
}

#endif
