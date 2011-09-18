#ifndef SANGUIS_MESSAGES_STRING_HPP_INCLUDED
#define SANGUIS_MESSAGES_STRING_HPP_INCLUDED

#include <sanguis/messages/bindings/dynamic_len.hpp>
#include <sanguis/messages/types/string.hpp>
#include <sanguis/messages/char_type.hpp>

namespace sanguis
{
namespace messages
{

typedef bindings::dynamic_len<
	messages::types::string,
	messages::char_type
> string;

}
}

#endif
