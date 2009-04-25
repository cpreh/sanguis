#ifndef SANGUIS_MESSAGES_HEALTH_HPP_INCLUDED
#define SANGUIS_MESSAGES_HEALTH_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"
#include "roles/health.hpp"
#include "space_unit.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		bind_entity_message<
			types::message::health
		>::type,
		majutsu::role<
			space_unit,
			roles::health
		>
	>
> health_elements;

typedef make_class<
	health_elements
>::type health;

}
}

#endif
