#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/difficulty.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/spawn_owner.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <fcppt/optional_impl.hpp>
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
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::server::difficulty const _difficulty
)
:
	sanguis::server::entities::base(),
	sanguis::server::entities::ifaces::with_angle(),
	sanguis::server::entities::with_links(),
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	enemy_type_(
		_enemy_type
	),
	difficulty_(
		_difficulty
	),
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
sanguis::server::entities::spawns::spawn::on_update()
{
	if(
		sanguis::server::entities::spawns::size_type const count_ =
			this->may_spawn()
	)
	{
		for(
			size_type i = 0;
			i < count_;
			++i
		)
			this->environment().insert(
				sanguis::server::entities::enemies::create(
					diff_clock_,
					random_generator_,
					enemy_type_,
					difficulty_,
					this->environment().load_context(),
					sanguis::server::entities::enemies::spawn_owner(
						this->link()
					)
				),
				sanguis::server::entities::insert_parameters(
					this->center(),
					this->angle()
				)
			);

		this->add_count(
			count_
		);
	}
}
