#include <sanguis/duration_second.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/ai/create_friend.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/friend.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/spawn.hpp>
#include <sanguis/server/weapons/spawn_parameters.hpp>
#include <sanguis/server/weapons/spawn_weapon.hpp>
#include <sanguis/server/weapons/spider.hpp>
#include <sanguis/server/weapons/spider_parameters.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/health.hpp>
#include <sanguis/server/weapons/attributes/make_health.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::weapons::spider::spider(
	sanguis::server::weapons::common_parameters const &_common_parameters,
	sanguis::server::weapons::spawn_weapon &&_spawn_weapon,
	sanguis::server::weapons::spider_parameters const &_parameters
)
:
	sanguis::server::weapons::spawn{
		_common_parameters,
		sanguis::weapon_type{
			sanguis::secondary_weapon_type::spider
		},
		std::move(
			_spawn_weapon
		),
		_parameters.range(),
		_parameters.backswing_time(),
		_parameters.cast_point(),
		sanguis::server::weapons::reload_time{
			sanguis::duration_second(
				60.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			)
		}
	},
	health_{
		_parameters.health()
	}
{
}

sanguis::server::weapons::spider::~spider()
= default;

sanguis::server::weapons::spider::spider(
	sanguis::server::weapons::spawn_parameters const &_spawn_parameters,
	sanguis::server::weapons::attributes::health const _health
)
:
	sanguis::server::weapons::spawn{
		_spawn_parameters
	},
	health_{
		_health
	}
{
}

sanguis::server::weapons::unique_ptr
sanguis::server::weapons::spider::clone() const
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::server::weapons::weapon
		>(
			fcppt::make_unique_ptr<
				sanguis::server::weapons::spider
			>(
				this->spawn_parameters(),
				health_
			)
		);
}

sanguis::server::entities::optional_base_ref
sanguis::server::weapons::spider::do_spawn(
	sanguis::server::weapons::attack const &_attack,
	sanguis::server::weapons::spawn_weapon const &_spawn_weapon
)
{
	return
		_attack.environment().insert(
			fcppt::unique_ptr_to_base<
				sanguis::server::entities::with_id
			>(
				fcppt::make_unique_ptr<
					sanguis::server::entities::friend_
				>(
					sanguis::friend_type::spider,
					_attack.environment().load_context(),
					sanguis::server::damage::no_armor(),
					health_.value(),
					sanguis::server::entities::movement_speed(
						100.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
					),
					sanguis::server::ai::create_friend(
						sanguis::server::ai::sight_range(
							1000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						),
						sanguis::server::entities::spawn_owner(
							this->owner().link()
						)
					),
					_spawn_weapon.get()()
				)
			),
			sanguis::server::entities::insert_parameters(
				sanguis::server::center(
					_attack.target().get()
				),
				_attack.angle()
			)
		);
}

sanguis::weapon_attribute_vector
sanguis::server::weapons::spider::extra_attributes() const
{
	return
		sanguis::weapon_attribute_vector{
			sanguis::server::weapons::attributes::make_health(
				health_
			)
		};
}
