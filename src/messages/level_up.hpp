#ifndef SANGUIS_MESSAGES_LEVEL_UP_HPP_INCLUDED
#define SANGUIS_MESSAGES_LEVEL_UP_HPP_INCLUDED

#include "types/message.hpp"
#include "bind_entity_message.hpp"
#include "level.hpp"
#include "make_class.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef make_class<
	 majutsu::composite<
		boost::mpl::vector2<
			bind_entity_message<
				types::message::level_up
			>::type,
			majutsu::role<
				messages::level
			>
		>
	> 
>::type level_up;

}
}

#endif
