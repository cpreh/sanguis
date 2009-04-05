#ifndef SANGUIS_MESSAGES_STRING_HPP_INCLUDED
#define SANGUIS_MESSAGES_STRING_HPP_INCLUDED

#include "bindings/dynamic_len.hpp"
#include "types/string.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::dynamic_len<
	types::string
> string;

}
}

#endif
