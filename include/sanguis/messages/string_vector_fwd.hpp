#ifndef SANGUIS_MESSAGES_STRING_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_STRING_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/messages/string_fwd.hpp>
#include <sanguis/messages/types/string_vector.hpp>
#include <alda/bindings/dynamic_len_decl.hpp>


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
