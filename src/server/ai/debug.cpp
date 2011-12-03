#include <sanguis/server/ai/debug.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/property/changeable_fwd.hpp>
#include <sanguis/server/entities/property/current_to_max.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/signed_angle_between_cast.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/try_dynamic_cast.hpp>

sanguis::server::ai::debug::debug(
	entities::with_ai &_me
)
:
	me_(_me)
{
}

sanguis::server::ai::debug::~debug()
{
}

void
sanguis::server::ai::debug::update()
{
	typedef fcppt::optional<
		server::space_unit
	> optional_angle;

	optional_angle const angle(
		fcppt::math::vector::signed_angle_between_cast<
			server::space_unit
		>(
			me_.center().get(),
			server::vector::null()
		)
	);

	if(
		angle
	)
	{
		FCPPT_TRY_DYNAMIC_CAST(
			entities::with_body *,
			with_body,
			&me_
		)
			with_body->angle(
				server::angle(
					*angle
				)
			);
	}

	FCPPT_TRY_DYNAMIC_CAST(
		entities::with_velocity *,
		movable,
		&me_
	)
	{
		entities::property::changeable &speed(
			movable->movement_speed()
		);

		if(
			angle
		)
			movable->direction(
				server::direction(
					*angle
				)
			);

		entities::property::current_to_max(
			speed
		);
	}
}
