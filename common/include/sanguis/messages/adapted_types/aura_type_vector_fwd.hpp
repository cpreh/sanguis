#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_AURA_TYPE_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_AURA_TYPE_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/messages/adapted_types/aura_type_fwd.hpp>
#include <alda/bindings/dynamic_len_decl.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
alda::bindings::dynamic_len<
	sanguis::aura_type_vector,
	sanguis::messages::adapted_types::aura_type
>
aura_type_vector;

}
}
}

#endif
