#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_STRING_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_STRING_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/dynamic_len_fwd.hpp>
#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/types/string_vector.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
sanguis::messages::adapted_types::dynamic_len<
	sanguis::messages::types::string_vector,
	sanguis::messages::adapted_types::string
>
string_vector;

}
}
}

#endif
