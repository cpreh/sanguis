#ifndef SANGUIS_MESSAGES_LEVEL_UP_HPP_INCLUDED
#define SANGUIS_MESSAGES_LEVEL_UP_HPP_INCLUDED

#include "types/message.hpp"
#include "bind_entity_message.hpp"
#include "level_type.hpp"
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
			types::message::level_up
		>::type,
		majutsu::role<
			level_type
		>
	>
> level_up_elements;

typedef make_class<
	level_up_elements
>::type level_up;

}
}

#endif
