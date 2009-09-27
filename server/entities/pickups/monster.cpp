#include "monster.hpp"
#include "../insert_parameters_pos.hpp"
#include "../friend.hpp"
#include "../../ai/simple.hpp"
#include "../../weapons/melee.hpp"
#include "../../environment/object.hpp"
#include "../../damage/no_armor.hpp"
#include "../../damage/list.hpp"
#include "../../../load/friend_name.hpp"
#include "../../../load/context.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/optional_impl.hpp>

sanguis::server::entities::pickups::monster::monster(
	server::environment::load_context_ptr const load_context,
	team::type const team_,
	friend_type::type const ftype
)
:
	pickup(
		pickup_type::monster,
		load_context,
		team_,
		optional_dim()
	),
	ftype(ftype)
{}

void
sanguis::server::entities::pickups::monster::do_pickup(
	base &receiver
)
{
	environment()->insert(
		entities::auto_ptr(
			new entities::friend_(
				ftype,
				environment()->load_context(),
				damage::no_armor(),
				health_type(100),
				server::movement_speed(100),
				ai::auto_ptr(
					new ai::simple(
						receiver.link()
					)
				),
				weapons::auto_ptr(
					new weapons::melee(
						weapons::range(100),
						weapons::base_cooldown(1),
						weapons::damage(5)
					)
				)
			)
		),
		entities::insert_parameters_pos(
			center()
		)
	);
}
