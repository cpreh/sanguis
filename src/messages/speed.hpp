#ifndef SANGUIS_MESSAGES_SPEED_HPP_INCLUDED
#define SANGUIS_MESSAGES_SPEED_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "vector2.hpp"
#include "types/message.hpp"
#include "roles/speed.hpp"
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
				types::message::speed
			>::type,
			majutsu::role<
				messages::vector2,
				roles::speed
			>
		>
	>
>::type speed;

}
}

#endif
