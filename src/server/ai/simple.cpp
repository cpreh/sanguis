#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/server/optional_angle.hpp>
#include <sanguis/server/ai/angle_to_target.hpp>
#include <sanguis/server/ai/move_to_target.hpp>
#include <sanguis/server/ai/rotate_to_target.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/stop.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/weapons/target.hpp>


sanguis::server::ai::simple::simple(
	sanguis::server::entities::with_ai &_me
)
:
	me_(
		_me
	),
	target_()
{
}

sanguis::server::ai::simple::~simple()
{
}

void
sanguis::server::ai::simple::in_range(
	sanguis::server::entities::with_body &_entity
)
{
	if(
		!target_
	)
		target_ =
			_entity.link();
}

void
sanguis::server::ai::simple::distance_changes(
	sanguis::server::entities::with_body &_entity
)
{
	if(
		!target_
	)
		target_ =
			_entity.link();

	// TODO: When do we pick up a new targets?
}

void
sanguis::server::ai::simple::update()
{
	sanguis::is_primary_weapon const weapon_to_use(
		true
	);

	if(
		!target_
	)
	{
		me_.use_weapon(
			false,
			weapon_to_use
		);

		sanguis::server::ai::stop(
			me_
		);

		return;
	}

	me_.target(
		sanguis::server::weapons::target(
			target_->center().get()
		)
	);

	me_.use_weapon(
		true,
		weapon_to_use
	);

	sanguis::server::optional_angle const angle_to_target(
		sanguis::server::ai::angle_to_target(
			me_,
			*target_
		)
	);

	if(
		angle_to_target
	)
		sanguis::server::ai::rotate_to_target(
			me_,
			*angle_to_target
		);

	sanguis::server::ai::move_to_target(
		me_,
		angle_to_target
	);
}
