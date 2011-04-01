#include "circle_ghost.hpp"
#include "../dim.hpp"
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/dim.hpp>

sanguis::server::collision::circle_ghost::circle_ghost(
	collision::ghost_parameters const &_params,
	server::pos const &_center,
	server::radius const _radius,
	collision::body_enter_callback const &_body_enter_callback,
	collision::body_exit_callback const &_body_exit_callback
)
:
	collision::ghost(
		_params,
		_center
		- server::dim(
			_radius.get(),
			_radius.get()
		),
		server::dim(
			_radius.get(),
			_radius.get()
		) * 2
	),
	radius_(_radius),
	body_enter_callback_(_body_enter_callback),
	body_exit_callback_(_body_exit_callback)
{
}

sanguis::server::collision::circle_ghost::~circle_ghost()
{
}

void
sanguis::server::collision::circle_ghost::on_body_enter(
	sge::projectile::body::object const &_body
)
{
	// TODO: track objects here and emit body_enter only if they enter the circle
	body_enter_callback_(
		_body
	);
}

void
sanguis::server::collision::circle_ghost::on_body_exit(
	sge::projectile::body::object const &_body
)
{
	body_exit_callback_(
		_body
	);
}
