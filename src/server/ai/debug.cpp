#include "debug.hpp"
#include "../entities/with_ai.hpp"
#include "../entities/with_body.hpp"
#include "../entities/with_velocity.hpp"
#include "../entities/property/changeable_fwd.hpp"
#include "../entities/property/current_to_max.hpp"
#include "../angle.hpp"
#include "../direction.hpp"
#include "../space_unit.hpp"
#include "../vector.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/signed_angle_cast.hpp>
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
sanguis::server::ai::debug::update(
	sanguis::time_delta const &
)
{
	typedef fcppt::optional<
		server::space_unit
	> optional_angle;

	optional_angle const angle(
		fcppt::math::vector::signed_angle_cast<
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
