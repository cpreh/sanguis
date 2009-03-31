#ifndef SANGUIS_MESSAGES_ENTITY_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ENTITY_MESSAGE_HPP_INCLUDED

#include "entity_id.hpp"
#include "message_type.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		message_type,
		majutsu::role<
			entity_id
		>
	>
> entity_message;

}
}

#endif
