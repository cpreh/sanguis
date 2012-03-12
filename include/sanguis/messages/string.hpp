#ifndef SANGUIS_MESSAGES_STRING_HPP_INCLUDED
#define SANGUIS_MESSAGES_STRING_HPP_INCLUDED

#include <sanguis/messages/types/string.hpp>
#include <sanguis/messages/char_type.hpp>
#include <alda/bindings/dynamic_len.hpp>


namespace sanguis
{
namespace messages
{

typedef alda::bindings::dynamic_len<
	sanguis::messages::types::string,
	sanguis::messages::char_type
> string;

}
}

#endif
