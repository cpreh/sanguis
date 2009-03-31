#ifndef SANGUIS_MESSAGES_ROTATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ROTATE_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "space_unit.hpp"
#include "types/message.hpp"
#include "roles/angle.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsus::composite<
	boost::mpl::vector<
		bind_entity_message<
			types::message::rotate
		>,
		majutsu::role<
			space_unit,
			roles::angle
		>
	>
> rotate_elements;

typedef make_class<
	rotate_elements
>::type rotate;

}
}

#endif
