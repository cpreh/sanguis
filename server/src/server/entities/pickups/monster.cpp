#include <sanguis/duration_second.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/friend_name.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/ai/create_friend.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/friend.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/pickups/monster.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::pickups::monster::monster(
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::friend_type const _friend_type,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
:
	sanguis::server::entities::pickups::pickup(
		sanguis::pickup_type::monster,
		_load_context,
		_team
	),
	random_generator_(
		_random_generator
	),
	friend_type_(
		_friend_type
	),
	difficulty_(
		_difficulty
	)
{
}

sanguis::server::entities::pickups::monster::~monster()
{
}

void
sanguis::server::entities::pickups::monster::do_pickup(
	sanguis::server::entities::base &_entity
)
{
	this->environment()->insert(
		fcppt::make_unique_ptr<
			sanguis::server::entities::friend_
		>(
			random_generator_,
			friend_type_,
			this->environment()->load_context(),
			sanguis::server::damage::no_armor(),
			sanguis::server::health(
				50.f
				*
				std::sqrt(
					difficulty_.get()
				)
			),
			sanguis::server::entities::movement_speed(
				100.f
			),
			sanguis::server::ai::create_friend(
				sanguis::server::ai::sight_range(
					1000.f
				),
				sanguis::server::entities::spawn_owner(
					dynamic_cast<
						sanguis::server::entities::ifaces::with_links &
					>(
						_entity
					).link()
				)
			),
			fcppt::make_unique_ptr<
				sanguis::server::weapons::melee
			>(
				random_generator_,
				sanguis::server::weapons::range(
					100.f
				),
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						1.f
					)
				),
				sanguis::server::weapons::damage(
					5.f
					*
					std::sqrt(
						difficulty_.get()
					)
				),
				sanguis::server::damage::list{
					sanguis::server::damage::normal =
						sanguis::server::damage::full
				}
			)
		),
		sanguis::server::entities::insert_parameters_center(
			this->center()
		)
	);
}
