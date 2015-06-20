#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_HEALTH_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_HEALTH_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
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
boost::mpl::vector2<
	majutsu::role<
		sanguis::messages::adapted_types::space_unit,
		sanguis::messages::roles::health
	>,
	majutsu::role<
		sanguis::messages::adapted_types::space_unit,
		sanguis::messages::roles::max_health
	>
>
add_with_health;

}
}
}
}

#endif
