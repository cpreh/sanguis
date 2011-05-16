#ifndef SANGUIS_MESSAGES_ROTATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ROTATE_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "space_unit.hpp"
#include "types/message.hpp"
#include "roles/angle.hpp"
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
			messages::bind_entity_message<
				types::message::rotate
			>::type,
			majutsu::role<
				messages::space_unit,
				roles::angle
			>
		>
	>
>::type rotate;

}
}

#endif
