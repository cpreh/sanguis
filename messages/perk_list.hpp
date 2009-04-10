#ifndef SANGUIS_MESSAGES_PERK_LIST_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_LIST_HPP_INCLUDED

#include "bindings/dynamic_len.hpp"
#include "bindings/pod.hpp"
#include "types/enum_vector.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::dynamic_len<
	types::enum_vector,
	bindings::pod
> perk_list;

}
}

#endif
