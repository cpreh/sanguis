#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/aux_/world/simple/body.hpp>
#include <sanguis/collision/aux_/world/simple/collides.hpp>
#include <sanguis/collision/aux_/world/simple/ghost.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sanguis/collision/world/group.hpp>
#include <fcppt/algorithm/map_iteration.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::aux_::world::simple::ghost::ghost(
	sanguis::collision::world::ghost_parameters const &_parameters,
	sanguis::collision::aux_::world::simple::ghost_remove_callback const &_ghost_remove_callback
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
	collision_group_(
		_parameters.collision_group()
	),
	center_(
		_parameters.center()
	),
	bodies_()
{
}

sanguis::collision::aux_::world::simple::ghost::~ghost()
{
	for(
		auto &body
		:
		bodies_
	)
		body_exit_callback_.get()(
			body.first->body_base()
		);

	ghost_remove_callback_(
		*this
	);
}

void
sanguis::collision::aux_::world::simple::ghost::center(
	sanguis::collision::center const _center
)
{
	center_ =
		_center;
}

sanguis::collision::center const
sanguis::collision::aux_::world::simple::ghost::center() const
{
	return
		center_;
}

sanguis::collision::radius const
sanguis::collision::aux_::world::simple::ghost::radius() const
{
	return
		radius_;
}

sanguis::collision::world::group
sanguis::collision::aux_::world::simple::ghost::collision_group() const
{
	return
		collision_group_;
}

void
sanguis::collision::aux_::world::simple::ghost::pre_update_bodies()
{
	for(
		auto &body
		:
		bodies_
	)
		body.second =
			body_status::marked_for_deletion;
}

void
sanguis::collision::aux_::world::simple::ghost::post_update_bodies()
{
	fcppt::algorithm::map_iteration(
		bodies_,
		[
			this
		](
			body_map::value_type const &_element
		)
		{
			if(
				_element.second
				==
				body_status::marked_for_deletion
			)
			{
				body_exit_callback_.get()(
					_element.first->body_base()
				);

				return
					true;
			}

			return false;
		}
	);
}

void
sanguis::collision::aux_::world::simple::ghost::update_near_body(
	sanguis::collision::aux_::world::simple::body const &_body
)
{
	bool const collides(
		sanguis::collision::aux_::world::simple::collides(
			_body,
			*this
		)
	);

	if(
		!collides
	)
		return;

	body_map::iterator const it(
		bodies_.find(
			&_body
		)
	);

	if(
		it == bodies_.end()
	)
	{
		bodies_.insert(
			std::make_pair(
				&_body,
				body_status::normal
			)
		);

		body_enter_callback_.get()(
			_body.body_base()
		);
	}
	else
		it->second =
			body_status::normal;
}

void
sanguis::collision::aux_::world::simple::ghost::new_body(
	sanguis::collision::aux_::world::simple::body const &_body
)
{
	if(
		sanguis::collision::aux_::world::simple::collides(
			_body,
			*this
		)
	)
	{
		bodies_.insert(
			std::make_pair(
				&_body,
				body_status::normal
			)
		);

		body_enter_callback_.get()(
			_body.body_base()
		);
	}
}

void
sanguis::collision::aux_::world::simple::ghost::remove_body(
	sanguis::collision::aux_::world::simple::body const &_body
)
{
	body_map::iterator const it(
		bodies_.find(
			&_body
		)
	);

	if(
		it != bodies_.end()
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
