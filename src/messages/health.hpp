#ifndef SANGUIS_MESSAGES_HEALTH_HPP_INCLUDED
#define SANGUIS_MESSAGES_HEALTH_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"
#include "roles/health.hpp"
#include "space_unit.hpp"
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
				types::message::health
			>::type,
			majutsu::role<
				messages::space_unit,
				roles::health
			>
		>
	> 
>::type health;

}
}

#endif
