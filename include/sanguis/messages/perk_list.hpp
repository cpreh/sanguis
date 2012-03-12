#ifndef SANGUIS_MESSAGES_PERK_LIST_HPP_INCLUDED
#define SANGUIS_MESSAGES_PERK_LIST_HPP_INCLUDED

#include <sanguis/messages/types/enum_vector.hpp>
#include <sanguis/messages/enum.hpp>
#include <alda/bindings/dynamic_len.hpp>


namespace sanguis
{
namespace messages
{

typedef alda::bindings::dynamic_len<
	sanguis::messages::types::enum_vector,
	sanguis::messages::enum_
> perk_list;

}
}

#endif
