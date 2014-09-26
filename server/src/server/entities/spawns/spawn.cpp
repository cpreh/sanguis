#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/assert/pre.hpp>


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
	sanguis::server::entities::base(),
	sanguis::server::entities::ifaces::with_angle(),
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

sanguis::server::center const
sanguis::server::entities::spawns::spawn::center() const
{
	FCPPT_ASSERT_PRE(
		center_
	);

	return
		*center_;
}

sanguis::server::angle const
sanguis::server::entities::spawns::spawn::angle() const
{
	FCPPT_ASSERT_PRE(
		angle_
	);

	return
		*angle_;
}

sanguis::server::team
sanguis::server::entities::spawns::spawn::team() const
{
	return
		sanguis::server::team::monsters;
}

bool
sanguis::server::entities::spawns::spawn::on_transfer(
	sanguis::server::entities::transfer_parameters const &_parameters
)
{
	center_ =
		_parameters.center();

	angle_ =
		_parameters.angle();

	return true;
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
				this->environment()->insert(
					sanguis::server::entities::enemies::create(
						random_generator_,
						enemy_type_,
						enemy_kind_,
						difficulty_,
						this->environment()->load_context(),
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
