#ifndef SANGUIS_MESSAGES_ADD_ELEMENTS_BASE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_ELEMENTS_BASE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/adapted_types/vector2_fwd.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef
majutsu::composite<
	boost::mpl::vector2<
		majutsu::role<
			sanguis::messages::adapted_types::vector2,
			sanguis::messages::roles::center
		>,
		majutsu::role<
			sanguis::messages::adapted_types::space_unit,
			sanguis::messages::roles::angle
		>
	>
>
add_elements_base;

}
}

#endif
