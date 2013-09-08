#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/aux/world/simple/body.hpp>
#include <sanguis/collision/aux/world/simple/collides.hpp>
#include <sanguis/collision/aux/world/simple/ghost.hpp>
#include <sanguis/collision/aux/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sanguis/collision/world/group_field.hpp>


sanguis::collision::aux::world::simple::ghost::ghost(
	sanguis::collision::world::ghost_parameters const &_parameters,
	sanguis::collision::aux::world::simple::ghost_remove_callback const &_ghost_remove_callback
)
:
	ghost_remove_callback_(
		_ghost_remove_callback
	),
	radius_(
		_parameters.radius()
	),
	body_enter_callback_(
		_parameters.body_enter_callback()
	),
	body_exit_callback_(
		_parameters.body_exit_callback()
	),
	collision_groups_(
		_parameters.collision_groups()
	),
	center_(
		_parameters.center()
	),
	bodies_()
{
}

sanguis::collision::aux::world::simple::ghost::~ghost()
{
	ghost_remove_callback_(
		*this
	);
}

void
sanguis::collision::aux::world::simple::ghost::center(
	sanguis::collision::center const _center
)
{
	center_ =
		_center;
}

sanguis::collision::center const
sanguis::collision::aux::world::simple::ghost::center() const
{
	return
		center_;
}

sanguis::collision::radius const
sanguis::collision::aux::world::simple::ghost::radius() const
{
	return
		radius_;
}

sanguis::collision::world::group_field const
sanguis::collision::aux::world::simple::ghost::collision_groups() const
{
	return
		collision_groups_;
}

void
sanguis::collision::aux::world::simple::ghost::update_body(
	sanguis::collision::aux::world::simple::body &_body
)
{
	bool const collides(
		sanguis::collision::aux::world::simple::collides(
			_body,
			*this
		)
	);

	body_set::iterator const it(
		bodies_.find(
			&_body
		)
	);

	if(
		it == bodies_.end()
		&&
		collides
	)
	{
		bodies_.insert(
			&_body
		);

		body_enter_callback_.get()(
			_body.body_base()
		);
	}
	else if(
		it != bodies_.end()
		&&
		!collides
	)
	{
		bodies_.erase(
			it
		);

		body_exit_callback_.get()(
			_body.body_base()
		);
	}
}
