#ifndef SANGUIS_MESSAGES_STRING_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_STRING_VECTOR_HPP_INCLUDED

#include "bindings/dynamic_len.hpp"
#include "types/string_vector.hpp"
#include "string.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::dynamic_len<
	messages::types::string_vector,
	messages::string
> string_vector;

}
}

#endif
