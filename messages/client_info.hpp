#ifndef SANGUIS_MESSAGES_CLIENT_INFO_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_INFO_HPP_INCLUDED

#include "types/message.hpp"
#include "string.hpp"
#include "make_class.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/constant.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		majutsu::constant<
			types::message::type,
			types::message::client_info
		>,
		majutsu::role<
			string
		>
	>
> client_info_elements;

typedef make_class<
	client_info_elements
>::type client_info;

}
}

#endif
