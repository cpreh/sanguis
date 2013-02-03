#include <sanguis/server/dim.hpp>
#include <sanguis/server/collision/body_base_fwd.hpp>
#include <sanguis/server/collision/body_enter_callback.hpp>
#include <sanguis/server/collision/body_exit_callback.hpp>
#include <sanguis/server/collision/circle_ghost.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>


sanguis::server::collision::circle_ghost::circle_ghost(
	sanguis::server::collision::group_vector const &_groups,
	sanguis::server::radius const _radius,
	sanguis::server::collision::body_enter_callback const &_body_enter_callback,
	sanguis::server::collision::body_exit_callback const &_body_exit_callback
)
:
	sanguis::server::collision::ghost(
		_groups,
		sanguis::server::dim(
			_radius.get(),
			_radius.get()
		) * 2.f
	),
	radius_(
		_radius
	),
	body_enter_callback_(
		_body_enter_callback
	),
	body_exit_callback_(
		_body_exit_callback
	)
{
}

sanguis::server::collision::circle_ghost::~circle_ghost()
{
}

void
sanguis::server::collision::circle_ghost::on_body_enter(
	sanguis::server::collision::body_base &_body
)
{
	// TODO: track objects here and emit body_enter only if they enter the circle
	body_enter_callback_.get()(
		_body
	);
}

void
sanguis::server::collision::circle_ghost::on_body_exit(
	sanguis::server::collision::body_base &_body
)
{
	body_exit_callback_.get()(
		_body
	);
}
