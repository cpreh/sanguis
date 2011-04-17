#ifndef SANGUIS_MESSAGES_PERK_LIST_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_LIST_HPP_INCLUDED

#include "bindings/dynamic_len.hpp"
#include "types/enum_vector.hpp"
#include "enum.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::dynamic_len<
	messages::types::enum_vector,
	messages::enum_
> perk_list;

}
}

#endif
