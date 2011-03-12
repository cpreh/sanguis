#ifndef SANGUIS_MESSAGES_MOVE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MOVE_HPP_INCLUDED

#include "types/message.hpp"
#include "bind_entity_message.hpp"
#include "pos.hpp"
#include "make_class.hpp"
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
			types::message::move
		>::type,
		majutsu::role<
			pos
		>
	>
> move_elements;

typedef make_class<
	move_elements
>::type move;

}
}

#endif
