#ifndef SANGUIS_MESSAGES_EXPERIENCE_HPP_INCLUDED
#define SANGUIS_MESSAGES_EXPERIENCE_HPP_INCLUDED

#include "types/message.hpp"
#include "roles/experience.hpp"
#include "bind_entity_message.hpp"
#include "exp_type.hpp"
#include "make_class.hpp"
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
			types::message::experience
		>::type,
		majutsu::role<
			exp_type,
			roles::experience
		>
	>
> experience_elements;

typedef make_class<
	experience_elements
>::type experience;

}
}

#endif
