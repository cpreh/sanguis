#ifndef SANGUIS_MESSAGES_ADD_ELEMENTS_BASE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_ELEMENTS_BASE_HPP_INCLUDED

#include "roles/angle.hpp"
#include "roles/center.hpp"
#include "space_unit.hpp"
#include "vector2.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector2<
		majutsu::role<
			messages::vector2,
			roles::center	
		>,
		majutsu::role<
			messages::space_unit,
			roles::angle
		>
	>
> add_elements_base;

}
}

#endif
