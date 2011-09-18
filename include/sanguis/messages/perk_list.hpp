#ifndef SANGUIS_MESSAGES_PERK_LIST_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_LIST_HPP_INCLUDED

#include <sanguis/messages/bindings/dynamic_len.hpp>
#include <sanguis/messages/types/enum_vector.hpp>
#include <sanguis/messages/enum.hpp>

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
