#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_STRING_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_STRING_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/char_type_fwd.hpp>
#include <sanguis/messages/types/string.hpp>
#include <alda/bindings/dynamic_len_decl.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
alda::bindings::dynamic_len<
	sanguis::messages::types::string,
	sanguis::messages::adapted_types::char_type
>
string;

}
}
}

#endif
