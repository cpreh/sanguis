#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_ELEMENTS_BASE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_ELEMENTS_BASE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/bool_fwd.hpp>
#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/adapted_types/vector2_fwd.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/created.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

typedef
metal::list<
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
>
add_elements_base;

}
}
}
}

#endif
