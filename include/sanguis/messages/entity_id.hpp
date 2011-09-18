#ifndef SANGUIS_MESSAGES_ENTITY_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_ENTITY_ID_HPP_INCLUDED

#include <sanguis/messages/bindings/fundamental_strong.hpp>
#include <sanguis/entity_id.hpp>

namespace sanguis
{
namespace messages
{

typedef bindings::fundamental_strong<
	sanguis::entity_id
> entity_id;

}
}

#endif
