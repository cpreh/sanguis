#ifndef SANGUIS_MESSAGES_WORLD_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_WORLD_ID_HPP_INCLUDED

#include "../world_id.hpp"
#include "bindings/fundamental_strong.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::fundamental_strong<
	sanguis::world_id
> world_id;

}
}

#endif
