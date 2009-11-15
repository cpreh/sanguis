#ifndef SANGUIS_MESSAGES_AVAILABLE_PERKS_HPP_INCLUDED
#define SANGUIS_MESSAGES_AVAILABLE_PERKS_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "perk_list.hpp"
#include "types/message.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector2<
		bind_entity_message<
			types::message::available_perks
		>::type,
		majutsu::role<
			perk_list
		>
	>
> available_perks_elements;

typedef make_class<
	available_perks_elements
>::type available_perks;

}
}

#endif
