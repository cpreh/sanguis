#ifndef SANGUIS_MESSAGES_STRING_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_STRING_FWD_HPP_INCLUDED

#include <sanguis/messages/char_type_fwd.hpp>
#include <sanguis/messages/types/string.hpp>
#include <alda/bindings/dynamic_len_fwd.hpp>


namespace sanguis
{
namespace messages
{

typedef
alda::bindings::dynamic_len<
	sanguis::messages::types::string,
	sanguis::messages::char_type
>
string;

}
}

#endif
