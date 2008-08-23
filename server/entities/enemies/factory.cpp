#include "factory.hpp"
#include "zombie.hpp"
#include "../../damage_types.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::auto_ptr
sanguis::server::entities::enemies::create(
	enemy_type::type const etype,
	environment const &env,
	messages::pos_type const &center,
	messages::space_unit const direction,
	messages::space_unit const angle)
{
	switch(etype) {
	case enemy_type::zombie:
		return auto_ptr(
			new zombie(
				env,
				damage::list(messages::mu(0)),
				center,
				direction,
				angle,
				boost::assign::map_list_of
					(entities::property::type::health,
					 entities::property(messages::mu(3)))
					(entities::property::type::movement_speed,
					 entities::property(messages::mu(50)))
				));
	default:
		throw sge::exception(
			SGE_TEXT("Invalid enemy_type in factory!"));
	}
}
