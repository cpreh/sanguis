#ifndef SANGUIS_MESSAGES_DISCONNECT_HPP_INCLUDED
#define SANGUIS_MESSAGES_DISCONNECT_HPP_INCLUDED

#include "types/message.hpp"
#include "make_class.hpp"
#include "make_message_id.hpp"
#include <majutsu/composite.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		make_message_id<
			types::message::disconnect
		>::type
	>
> disconnect_elements;

typedef make_class<
	disconnect_elements
>::type disconnect;

}
}

#endif
