#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_ENTITY_ID_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_ENTITY_ID_FWD_HPP_INCLUDED

#include <sanguis/entity_id_fwd.hpp>
#include <sanguis/entity_id_type.hpp>
#include <sanguis/messages/adapted_types/unsigned_fwd.hpp>
#include <alda/bindings/strong_typedef_decl.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
alda::bindings::strong_typedef<
	sanguis::entity_id,
	sanguis::messages::adapted_types::unsigned_<
		sanguis::entity_id_type
	>
>
entity_id;

}
}
}

#endif
