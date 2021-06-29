#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_ELEMENTS_BASE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_ELEMENTS_BASE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/bool_fwd.hpp>
#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/adapted_types/vector2_fwd.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/created.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

using
add_elements_base
=
fcppt::mpl::list::object<
	fcppt::record::element<
		sanguis::messages::roles::center,
		sanguis::messages::adapted_types::vector2
	>,
	fcppt::record::element<
		sanguis::messages::roles::angle,
		sanguis::messages::adapted_types::space_unit
	>,
	fcppt::record::element<
		sanguis::messages::roles::created,
		sanguis::messages::adapted_types::bool_
	>
>;

}
}
}
}

#endif
