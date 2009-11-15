#ifndef SANGUIS_MESSAGES_ADD_ELEMENTS_BASE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_ELEMENTS_BASE_HPP_INCLUDED

#include "roles/angle.hpp"
#include "pos.hpp"
#include "space_unit.hpp"
#include "dim.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector3<
		majutsu::role<
			pos
		>,
		majutsu::role<
			space_unit,
			roles::angle
		>,
		majutsu::role<
			dim
		>
	>
> add_elements_base;

}
}

#endif
