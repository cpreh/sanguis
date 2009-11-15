#ifndef SANGUIS_MESSAGES_CONNECT_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONNECT_HPP_INCLUDED

#include "types/message.hpp"
#include "make_class.hpp"
#include "make_message_id.hpp"
#include <majutsu/composite.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector1<
		make_message_id<
			types::message::connect
		>::type
	>
> connect_elements;

typedef make_class<
	connect_elements
>::type connect;

}
}

#endif
