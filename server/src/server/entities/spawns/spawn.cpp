#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/simple.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/assert/optional_error.hpp>


void
sanguis::server::entities::spawns::spawn::unregister(
	sanguis::server::entities::base &
)
{
}

sanguis::server::entities::spawns::spawn::~spawn()
{
}

sanguis::server::entities::spawns::spawn::spawn(
	sanguis::random_generator &_random_generator,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::creator::enemy_kind const _enemy_kind,
	sanguis::server::world::difficulty const _difficulty
)
:
	sanguis::server::entities::ifaces::with_angle(),
	sanguis::server::entities::simple(),
	sanguis::server::entities::with_links(),
	random_generator_(
		_random_generator
	),
	enemy_type_{
		_enemy_type
	},
	enemy_kind_{
		_enemy_kind
	},
	difficulty_{
		_difficulty
	},
	center_(),
	angle_()
{
}

sanguis::server::center
sanguis::server::entities::spawns::spawn::center() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			center_
		);
}

sanguis::server::angle
sanguis::server::entities::spawns::spawn::angle() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			angle_
		);
}

void
sanguis::server::entities::spawns::spawn::angle(
	sanguis::server::angle const _angle
)
{
	angle_ =
		optional_angle(
			_angle
		);
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::spawns::spawn::on_transfer(
	sanguis::server::entities::transfer_parameters const &_parameters
)
{
	center_ =
		optional_center(
			_parameters.center()
		);

	angle_ =
		optional_angle(
			_parameters.angle()
		);

	return
		sanguis::server::entities::optional_transfer_result(
			sanguis::server::entities::transfer_result()
		);
}

void
sanguis::server::entities::spawns::spawn::update()
{
	if(
		sanguis::server::entities::spawns::size_type const cur_count =
			this->may_spawn()
	)
	{
		fcppt::algorithm::repeat(
			cur_count,
			[
				this
			]()
			{
				sanguis::server::environment::object &cur_environment(
					FCPPT_ASSERT_OPTIONAL_ERROR(
						this->environment()
					)
				);

				sanguis::server::environment::insert_no_result(
					cur_environment,
					sanguis::server::entities::enemies::create(
						random_generator_,
						enemy_type_,
						enemy_kind_,
						difficulty_,
						cur_environment.load_context(),
						sanguis::server::entities::spawn_owner(
							this->link()
						),
						sanguis::server::entities::enemies::special_chance(
							0.05f
						)
					),
					sanguis::server::entities::insert_parameters(
						this->center(),
						this->angle()
					)
				);
			}
		);

		this->add_count(
			cur_count
		);
	}
}
