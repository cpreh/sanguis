#ifndef SANGUIS_MESSAGES_ADD_WITH_SPEED_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_WITH_SPEED_HPP_INCLUDED

#include "roles/speed.hpp"
#include "vector2.hpp"
#include "add_elements_base.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		add_elements_base,
		majutsu::role<
			vector2,
			roles::speed
		>
	>
> add_with_speed;

}
}

#endif
