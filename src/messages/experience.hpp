#ifndef SANGUIS_MESSAGES_EXPERIENCE_HPP_INCLUDED
#define SANGUIS_MESSAGES_EXPERIENCE_HPP_INCLUDED

#include "types/message.hpp"
#include "roles/experience.hpp"
#include "bind_entity_message.hpp"
#include "exp.hpp"
#include "make_class.hpp"
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
				types::message::experience
			>::type,
			majutsu::role<
				messages::exp,
				roles::experience
			>
		>
	> 
>::type experience;

}
}

#endif
