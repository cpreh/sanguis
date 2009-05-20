#include "monster.hpp"
#include "../base_parameters.hpp"
#include "../friend.hpp"
#include "../property.hpp"
#include "../../ai/simple.hpp"
#include "../../weapons/melee.hpp"
#include "../../get_dim.hpp"
#include "../../environment.hpp"
#include "../../damage/no_armor.hpp"
#include "../../damage/list.hpp"
#include "../../../load/friend_name.hpp"
#include "../../../load/context.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/optional_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::pickups::monster::monster(
	server::environment const &env,
	pos_type const &center,
	team::type const team_,
	friend_type::type const ftype)
:
	pickup(
		pickup_type::monster,
		env,
		center,
		team_,
		optional_dim()
	),
	ftype(ftype)
{}

void sanguis::server::entities::pickups::monster::do_pickup(
	entity_with_weapon &receiver)
{
	insert(
		entities::auto_ptr(
			new entities::friend_(
				ftype,
				environment(),
				damage::no_armor(),
				center(),
				static_cast<space_unit>(0), // angle TODO
				static_cast<space_unit>(0), // direction TODO
				receiver.team(),
				boost::assign::map_list_of
				(
					entities::property_type::health,
					entities::property(
						static_cast<space_unit>(100)
					)
				)
				(
					entities::property_type::movement_speed,
					entities::property(
						static_cast<space_unit>(100)
					)
				),
				ai::auto_ptr(
					new ai::simple(
						receiver.link()
					)
				),
				weapons::auto_ptr(
					new weapons::melee(
						environment(),
						static_cast<space_unit>(100), // range
						static_cast<time_type>(1), // cooldown
						static_cast<space_unit>(5) // damage
					)
				)
			)
		)
	);
}
