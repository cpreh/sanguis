#include "circle_ghost.hpp"
#include "../dim.hpp"
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/dim.hpp>

sanguis::server::collision::circle_ghost::circle_ghost(
	collision::ghost_parameters const &_params,
	server::pos const &_center,
	server::space_unit const _radius
)
:
	collision::ghost(
		_params,
		_center
		- server::dim(
			_radius,
			_radius
		),
		server::dim(
			_radius,
			_radius
		) * 2
	),
	radius_(_radius)
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
}

void
sanguis::server::collision::circle_ghost::on_body_exit(
	sge::projectile::body::object const &_body
)
{
}
