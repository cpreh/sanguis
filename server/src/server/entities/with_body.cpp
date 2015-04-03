#include <sanguis/collision/center.hpp>
#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/result.hpp>
#include <sanguis/server/entities/combine_remove_from_world.hpp>
#include <sanguis/server/entities/combine_transfer.hpp>
#include <sanguis/server/entities/convert_model_size.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/radius.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/try_dynamic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_body::with_body(
	sanguis::server::model_size const _model_size
)
:
	sanguis::server::entities::with_ghosts(),
	sanguis::server::entities::ifaces::with_angle(),
	sanguis::server::entities::ifaces::with_id(),
	sanguis::server::entities::ifaces::with_links(),
	sanguis::collision::world::body_base(),
	dim_(
		sanguis::server::entities::convert_model_size(
			_model_size
		)
	),
	angle_(
		fcppt::literal<
			sanguis::server::space_unit
		>(
			0
		)
	),
	collision_body_(
		sanguis::server::entities::radius(
			dim_
		),
		*this
	),
	net_angle_(
		this->diff_clock()
	)
{
}

sanguis::server::entities::with_body::~with_body()
{
}

sanguis::server::center const
sanguis::server::entities::with_body::center() const
{
	return
		collision_body_.center();
}

sanguis::server::angle const
sanguis::server::entities::with_body::angle() const
{
	return
		angle_;
}

void
sanguis::server::entities::with_body::center(
	sanguis::server::center const &_center
)
{
	collision_body_.center(
		_center
	);
}

void
sanguis::server::entities::with_body::angle(
	sanguis::server::angle const _angle
)
{
	angle_ =
		_angle;

	net_angle_.set(
		angle_
	);
}

sanguis::server::radius const
sanguis::server::entities::with_body::radius() const
{
	return
		collision_body_.radius();
}

sanguis::server::dim const
sanguis::server::entities::with_body::dim() const
{
	return
		dim_;
}

sanguis::server::entities::remove_from_world_result
sanguis::server::entities::with_body::remove_from_world()
{
	// Make sure all links are gone before the body is destroyed
	this->reset_links();

	return
		sanguis::server::entities::combine_remove_from_world(
			sanguis::server::entities::with_ghosts::remove_from_world(),
			sanguis::server::entities::remove_from_world_result(
				collision_body_.remove(
					this->environment()->collision_world()
				)
			)
		);
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::with_body::on_transfer(
	sanguis::server::entities::transfer_parameters const &_parameters
)
{
	net_angle_.reset();

	this->angle(
		_parameters.angle()
	);

	// TODO: Use optional_bind
	sanguis::server::entities::optional_transfer_result ghost_result(
		sanguis::server::entities::with_ghosts::on_transfer(
			_parameters
		)
	);

	FCPPT_ASSERT_ERROR(
		ghost_result
	);

	return
		sanguis::server::entities::optional_transfer_result(
			sanguis::server::entities::combine_transfer(
				sanguis::server::entities::transfer_result(
					collision_body_.transfer(
						_parameters.world(),
						_parameters.created(),
						_parameters.center(),
						this->initial_speed(),
						this->collision_group()
					)
				),
				std::move(
					*ghost_result
				)
			)
		);
}

void
sanguis::server::entities::with_body::update()
{
	if(
		net_angle_.update()
	)
		this->environment()->angle_changed(
			this->id(),
			this->angle()
		);
}

void
sanguis::server::entities::with_body::on_world_collision(
	sanguis::server::collision::result const &_result
)
{
	this->center(
		_result.center()
	);

	this->body_speed(
		_result.speed()
	);
}

void
sanguis::server::entities::with_body::body_speed(
	sanguis::server::speed const _speed
)
{
	collision_body_.speed(
		_speed
	);

	this->on_speed_change(
		_speed
	);
}

sanguis::server::speed const
sanguis::server::entities::with_body::body_speed() const
{
	return
		collision_body_.speed();
}

boost::logic::tribool const
sanguis::server::entities::with_body::can_collide_with(
	sanguis::collision::world::body_base const &_body_base
) const
{
	return
		fcppt::maybe(
			fcppt::cast::try_dynamic<
				sanguis::server::entities::with_body const &
			>(
				_body_base
			),
			[]{
				return
					boost::logic::tribool{
						boost::logic::indeterminate
					};
			},
			[
				this
			](
				sanguis::server::entities::with_body const &_entity
			)
			{
				return
					boost::logic::tribool{
						this->can_collide_with_body(
							_entity
						)
					};
			}
		);
}

void
sanguis::server::entities::with_body::collision(
	sanguis::collision::world::body_base &_body_base
)
{
	fcppt::maybe_void(
		fcppt::cast::try_dynamic<
			sanguis::server::entities::with_body &
		>(
			_body_base
		),
		[
			this
		](
			sanguis::server::entities::with_body &_entity
		)
		{
			this->collision_with_body(
				_entity
			);
		}
	);
}

boost::logic::tribool const
sanguis::server::entities::with_body::can_collide_with_body(
	sanguis::server::entities::with_body const &
) const
{
	return
		boost::logic::indeterminate;
}

void
sanguis::server::entities::with_body::collision_with_body(
	sanguis::server::entities::with_body &
)
{
}

void
sanguis::server::entities::with_body::center_changed(
	sanguis::collision::center const _center
)
{
	sanguis::server::center const server_center(
		_center.get()
	);

	this->update_ghost_center(
		server_center
	);

	this->on_position_change(
		server_center
	);
}

sanguis::server::speed const
sanguis::server::entities::with_body::initial_speed() const
{
	return
		sanguis::server::speed(
			sanguis::server::speed::value_type::null()
		);
}

void
sanguis::server::entities::with_body::on_position_change(
	sanguis::server::center
)
{
}

void
sanguis::server::entities::with_body::on_speed_change(
	sanguis::server::speed
)
{
}
