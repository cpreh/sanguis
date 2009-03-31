#ifndef SANGUIS_MESSAGES_MOVE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MOVE_HPP_INCLUDED

#include "types/message.hpp"
#include "entity_message.hpp"
#include "pos.hpp"
#include "make_class.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>


namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		bind_entity_message<
			types::message::move
		>,
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
