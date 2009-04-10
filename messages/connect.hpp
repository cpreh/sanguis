#ifndef SANGUIS_MESSAGES_CONNECT_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONNECT_HPP_INCLUDED

#include "types/message.hpp"
#include "roles/followup.hpp"
#include "make_class.hpp"
#include "enum.hpp"
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
			types::message::connect
		>::type,
		majutsu::role<
			enum_,
			roles::followup
		>
	>
> connect_elements;

typedef make_class<
	connect_elements
>::type connect;

}
}

#endif
