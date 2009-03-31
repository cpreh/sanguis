#ifndef SANGUIS_MESSAGES_ADD_PICKUP_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PICKUP_HPP_INCLUDED

#include "make_add_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "types/message.hpp"
#include "roles/pickup_type.hpp"
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef make_add_message<
	types::message::add_pickup,
	boost::mpl::vector<
		majutsu::role<
			enum_,
			roles::pickup_type
		>
	>
> add_pickup_elements;

typedef make_class<
	add_pickup_elements
> add_pickup;


}
}

#endif
