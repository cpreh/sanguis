#ifndef SANGUIS_MESSAGES_ADD_WITH_HEALTH_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_WITH_HEALTH_HPP_INCLUDED

#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <sanguis/messages/add_with_speed.hpp>
#include <sanguis/messages/space_unit.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector3<
		messages::add_with_speed,
		majutsu::role<
			messages::space_unit,
			roles::health
		>,
		majutsu::role<
			messages::space_unit,
			roles::max_health
		>
	>
> add_with_health;

}
}

#endif
