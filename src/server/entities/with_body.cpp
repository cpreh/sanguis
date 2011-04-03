#include "with_body.hpp"
#include "collision_groups.hpp"
#include "solidity.hpp"
#include "transfer_parameters.hpp"
#include "../collision/body.hpp"
#include "../collision/user_data.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/assert.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::entities::with_body::with_body()
:
	collision_body_(),
	angle_(0)
{
}

sanguis::server::entities::with_body::~with_body()
{
}

sanguis::server::angle const
sanguis::server::entities::with_body::angle() const
{
	return angle_;
}

sanguis::server::center const
sanguis::server::entities::with_body::center() const
{
	FCPPT_ASSERT(
		collision_body_
	);

	return
		collision_body_->center();
}

void
sanguis::server::entities::with_body::center(
	server::center const &_center
)
{
	FCPPT_ASSERT(
		collision_body_
	);

	collision_body_->center(
		_center
	);
}

void
sanguis::server::entities::with_body::speed(
	server::speed const &_speed
)
{
	FCPPT_ASSERT(
		collision_body_
	);

	collision_body_->speed(
		_speed
	);
}

void
sanguis::server::entities::with_body::angle(
	server::angle const _angle
)
{
	angle_ = _angle;
}

void
sanguis::server::entities::with_body::on_transfer(
	entities::transfer_parameters const &_params
)
{
	this->angle(
		_params.angle()
	);

	collision_body_.take(
		fcppt::make_unique_ptr<
			collision::body
		>(
			_params.create_parameters(),
			this->initial_direction(),
			entities::collision_groups(
				this->type(),
				this->team()
			),
			this->recreate_shape(),
			entities::solidity(
				this->type()
			),
			collision::user_data(
				*this
			),
			std::tr1::bind(
				&with_body::on_position_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	with_ghosts::on_transfer(
		_params
	);
}

void
sanguis::server::entities::with_body::on_position_change(
	server::center const &_center
)
{
	with_ghosts::update_center(
		_center
	);
}

boost::logic::tribool const
sanguis::server::entities::with_body::can_collide_with(
	collision::body_base const &_body_base
) const
{
	FCPPT_TRY_DYNAMIC_CAST(
		entities::with_body const *,
		entity,
		&_body_base
	)
		return
			this->can_collide_with_body(
				*entity
			);
	
	return boost::logic::indeterminate;
}

void
sanguis::server::entities::with_body::collide(
	collision::body_base &_body_base
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		entities::with_body *,
		entity,
		&_body_base
	)
		this->collision_with_body(
			*entity
		);
}

boost::logic::tribool const
sanguis::server::entities::with_body::can_collide_with_body(
	entities::with_body const &
) const
{
	return boost::logic::indeterminate;
}

void
sanguis::server::entities::with_body::collision_with_body(
	entities::with_body &
)
{
}

sanguis::server::speed const
sanguis::server::entities::with_body::initial_direction() const
{
	return
		server::speed(
			server::speed::value_type::null()
		);
}
