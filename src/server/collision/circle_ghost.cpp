#include "circle_ghost.hpp"
#include "../dim.hpp"
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/dim.hpp>

sanguis::server::collision::circle_ghost::circle_ghost(
	collision::group_vector const &_groups,
	server::radius const _radius,
	collision::body_enter_callback const &_body_enter_callback,
	collision::body_exit_callback const &_body_exit_callback
)
:
	collision::ghost(
		_groups,
		server::dim(
			_radius.get(),
			_radius.get()
		) * 2.f
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
	collision::body_base &_body
)
{
	// TODO: track objects here and emit body_enter only if they enter the circle
	body_enter_callback_.get()(
		_body
	);
}

void
sanguis::server::collision::circle_ghost::on_body_exit(
	collision::body_base &_body
)
{
	body_exit_callback_.get()(
		_body
	);
}
