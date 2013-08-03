#ifndef SANGUIS_MESSAGES_STRING_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_STRING_VECTOR_HPP_INCLUDED

#include <sanguis/messages/string.hpp>
#include <sanguis/messages/types/string_vector.hpp>
#include <alda/bindings/dynamic_len.hpp>


namespace sanguis
{
namespace messages
{

typedef
alda::bindings::dynamic_len<
	sanguis::messages::types::string_vector,
	sanguis::messages::string
>
string_vector;

}
}

#endif
