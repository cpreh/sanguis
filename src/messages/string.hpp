#ifndef SANGUIS_MESSAGES_STRING_HPP_INCLUDED
#define SANGUIS_MESSAGES_STRING_HPP_INCLUDED

#include "bindings/dynamic_len.hpp"
#include "types/string.hpp"
#include "char_type.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::dynamic_len<
	types::string,
	char_type
> string;

}
}

#endif
