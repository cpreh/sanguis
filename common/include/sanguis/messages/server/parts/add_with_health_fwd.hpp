#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_HEALTH_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_HEALTH_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
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

using
add_with_health
=
metal::list<
	fcppt::record::element<
		sanguis::messages::roles::health,
		sanguis::messages::adapted_types::space_unit
	>,
	fcppt::record::element<
		sanguis::messages::roles::max_health,
		sanguis::messages::adapted_types::space_unit
	>
>;

}
}
}
}

#endif
