#ifndef SANGUIS_MESSAGES_ENTITY_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_ENTITY_ID_HPP_INCLUDED

#include "../entity_id.hpp"
#include <majutsu/pod.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::pod<
	sanguis::entity_id
> entity_id;

}
}

#endif
