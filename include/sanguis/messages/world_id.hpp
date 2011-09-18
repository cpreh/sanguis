#ifndef SANGUIS_MESSAGES_WORLD_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_WORLD_ID_HPP_INCLUDED

#include <sanguis/messages/bindings/fundamental_strong.hpp>
#include <sanguis/world_id.hpp>

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
