#ifndef SANGUIS_MESSAGES_ENTITY_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_ENTITY_ID_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <alda/bindings/fundamental_strong.hpp>


namespace sanguis
{
namespace messages
{

typedef alda::bindings::fundamental_strong<
	sanguis::entity_id
> entity_id;

}
}

#endif
