#ifndef SANGUIS_MESSAGES_SPEED_HPP_INCLUDED
#define SANGUIS_MESSAGES_SPEED_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "vector2.hpp"
#include "types/message.hpp"
#include "roles/speed.hpp"
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
			types::message::speed
		>::type,
		majutsu::role<
			vector2,
			roles::speed
		>
	>
> speed_elements;

typedef make_class<
	speed_elements
>::type speed;

}
}

#endif
