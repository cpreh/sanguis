#ifndef SANGUIS_MESSAGES_NET_ERROR_HPP_INCLUDED
#define SANGUIS_MESSAGES_NET_ERROR_HPP_INCLUDED

#include "string.hpp"
#include "types/message.hpp"
#include "roles/error_message.hpp"
#include "make_class.hpp"
#include "make_message_id.hpp"
#include <majutsu/composite.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector2<
		make_message_id<
			types::message::net_error
		>::type,
		majutsu::role<
			string,
			roles::error_message
		>
	>
> net_error_elements;

typedef make_class<
	net_error_elements
>::type net_error;

}
}

#endif
