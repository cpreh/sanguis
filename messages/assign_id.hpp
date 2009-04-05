#ifndef SANGUIS_MESSAGES_ASSIGN_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_ASSIGN_ID_HPP_INCLUDED

#include "types/message.hpp"
#include "roles/entity_id.hpp"
#include "make_class.hpp"
#include "make_message_id.hpp"
#include "entity_id.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		make_message_id<
			types::message::assign_id
		>::type,
		majutsu::role<
			entity_id,
			roles::entity_id
		>
	>
> assign_id_elements;

typedef make_class<
	assign_id_elements
>::type assign_id;

}
}

#endif
