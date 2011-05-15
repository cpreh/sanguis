#ifndef SANGUIS_MESSAGES_CLIENT_INFO_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_INFO_HPP_INCLUDED

#include "types/message.hpp"
#include "string.hpp"
#include "make_class.hpp"
#include "make_message_id.hpp"
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
			messages::make_message_id<
				types::message::client_info
			>::type,
			majutsu::role<
				messages::string
			>
		>
	> 
>::type client_info;

}
}

#endif
