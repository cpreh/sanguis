#ifndef SANGUIS_MESSAGES_ASSIGN_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_ASSIGN_ID_HPP_INCLUDED

#include "types/message.hpp"
#include "roles/followup.hpp"
#include "enum.hpp"
#include "make_class.hpp"
#include "bind_entity_message.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector2<
		bind_entity_message<
			types::message::assign_id
		>::type,
		majutsu::role<
			enum_,
			roles::followup
		>
	>
> assign_id_elements;

typedef make_class<
	assign_id_elements
>::type assign_id;

}
}

#endif
