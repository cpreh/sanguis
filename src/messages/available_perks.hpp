#ifndef SANGUIS_MESSAGES_AVAILABLE_PERKS_HPP_INCLUDED
#define SANGUIS_MESSAGES_AVAILABLE_PERKS_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "perk_tree.hpp"
#include "types/message.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			messages::bind_entity_message<
				types::message::available_perks
			>::type,
			majutsu::role<
				messages::perk_tree
			>
		>
	>
>::type available_perks;

}
}

#endif
