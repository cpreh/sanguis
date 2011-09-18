#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/body_parameters.hpp>
#include <sanguis/server/entities/collision_groups.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/make_groups.hpp>
#include <sanguis/server/collision/user_data.hpp>
#include <sge/projectile/body/scoped.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::with_body::with_body(
	entities::body_parameters const &_params
)
:
	collision_body_(
		fcppt::make_unique_ptr<
			collision::body
		>(
			server::center(
				server::center::value_type::null()
			),
			server::speed(
				server::speed::value_type::null()
			),
			server::angle(
				0
			),
			_params.shape(),
			_params.solidity(),
			collision::user_data(
				*this
			),
			std::tr1::bind(
				&with_body::on_position_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	scoped_body_()
{
}

sanguis::server::entities::with_body::~with_body()
{
	FCPPT_ASSERT_PRE(
		!scoped_body_
	);
}

sanguis::server::angle const
sanguis::server::entities::with_body::angle() const
{
	return
		collision_body_->angle();
}

sanguis::server::center const
sanguis::server::entities::with_body::center() const
{
	return
		collision_body_->center();
}

void
sanguis::server::entities::with_body::center(
	server::center const &_center
)
{
	collision_body_->center(
		_center
	);
}

void
sanguis::server::entities::with_body::speed(
	server::speed const &_speed
)
{
	collision_body_->speed(
		_speed
	);
}

void
sanguis::server::entities::with_body::angle(
	server::angle const _angle
)
{
	collision_body_->angle(
		_angle
	);
}

void
sanguis::server::entities::with_body::on_transfer(
	entities::transfer_parameters const &_params
)
{
	collision_body_->angle(
		_params.angle()
	);

	collision_body_->center(
		_params.center()
	);

	collision_body_->speed(
		this->initial_speed()
	);

	scoped_body_.take(
		fcppt::make_unique_ptr<
			sge::projectile::body::scoped
		>(
			fcppt::ref(
				_params.world()
			),
			fcppt::ref(
				collision_body_->get()
			),
			collision::make_groups(
				entities::collision_groups(
					this->type(),
					this->team()
				),
				_params.global_groups()
			)
		)
	);

	with_ghosts::on_transfer(
		_params
	);
}

void
sanguis::server::entities::with_body::on_destroy()
{
	scoped_body_.reset();

	with_ghosts::on_destroy();
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
sanguis::server::entities::with_body::collision(
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

void
sanguis::server::entities::with_body::reset_speed(
	server::speed const &_speed
)
{
	this->speed(
		_speed
	);
}
