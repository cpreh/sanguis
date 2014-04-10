#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_STRING_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_STRING_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/types/string_vector.hpp>
#include <alda/bindings/dynamic_len_decl.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
alda::bindings::dynamic_len<
	sanguis::messages::types::string_vector,
	sanguis::messages::adapted_types::string
>
string_vector;

}
}
}

#endif
