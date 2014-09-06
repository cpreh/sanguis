#include <sanguis/random_generator.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/is_unique.hpp>
#include <sanguis/server/entities/enemies/normal.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/make.hpp>
#include <sanguis/server/entities/enemies/factory/make_special.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::make(
	sanguis::server::entities::enemies::factory::parameters const &_parameters,
	sanguis::server::damage::armor_array const &_armor,
	sanguis::server::health const _health,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::ai::create_function const &_ai_create_function,
	sanguis::server::weapons::unique_ptr &&_weapon,
	sanguis::server::pickup_probability const _pickup_probability,
	sanguis::server::exp const _exp,
	sanguis::server::auras::container &&_auras
)
{
	sanguis::server::entities::enemies::parameters parameters(
		_parameters.enemy_type(),
		_parameters.load_context(),
		_armor,
		_health,
		_movement_speed,
		_ai_create_function,
		std::move(
			_weapon
		),
		_pickup_probability,
		_exp,
		_parameters.difficulty(),
		_parameters.spawn_owner(),
		std::move(
			_auras
		)
	);

	typedef
	fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			float
		>
	>
	distribution_type;

	distribution_type distribution(
		distribution_type::param_type(
			distribution_type::param_type::min(
				0.f
			),
			distribution_type::param_type::sup(
				1.f
			)
		)
	);

	sanguis::server::entities::enemies::is_unique const is_unique{
		_parameters.enemy_kind()
		==
		sanguis::creator::enemy_kind::unique
	};

	return
		is_unique.get()
		||
		distribution(
			_parameters.random_generator()
		)
		<
		_parameters.special_chance().get()
		?
			sanguis::server::entities::enemies::factory::make_special(
				_parameters.random_generator(),
				std::move(
					parameters
				),
				is_unique
			)
		:
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::normal
			>(
				std::move(
					parameters
				)
			)
		;
}
