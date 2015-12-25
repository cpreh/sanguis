#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/impl/collides.hpp>
#include <sanguis/collision/impl/world/make_circle.hpp>
#include <sanguis/collision/impl/world/simple/body.hpp>
#include <sanguis/collision/impl/world/simple/ghost.hpp>
#include <sanguis/collision/impl/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/world/body_enter.hpp>
#include <sanguis/collision/world/body_exit.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sanguis/collision/world/optional_body_enter.hpp>
#include <sanguis/collision/world/optional_body_exit.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/optional_map.hpp>
#include <fcppt/reference_wrapper_comparison.hpp>
#include <fcppt/algorithm/map_iteration.hpp>
#include <fcppt/algorithm/update_action.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::impl::world::simple::ghost::ghost(
	sanguis::collision::world::ghost_parameters const &_parameters,
	sanguis::collision::impl::world::simple::ghost_remove_callback const &_ghost_remove_callback
)
:
	ghost_remove_callback_(
		_ghost_remove_callback
	),
	radius_(
		_parameters.radius()
	),
	collision_group_(
		_parameters.collision_group()
	),
	center_(
		_parameters.center()
	),
	ghost_base_(
		_parameters.ghost_base()
	),
	bodies_()
{
}

sanguis::collision::impl::world::simple::ghost::~ghost()
{
	ghost_remove_callback_(
		*this
	);
}

void
sanguis::collision::impl::world::simple::ghost::center(
	sanguis::collision::center const _center
)
{
	center_ =
		_center;
}

sanguis::collision::center
sanguis::collision::impl::world::simple::ghost::center() const
{
	return
		center_;
}

sanguis::collision::radius
sanguis::collision::impl::world::simple::ghost::radius() const
{
	return
		radius_;
}

sanguis::collision::world::ghost_group
sanguis::collision::impl::world::simple::ghost::collision_group() const
{
	return
		collision_group_;
}

void
sanguis::collision::impl::world::simple::ghost::pre_update_bodies()
{
	for(
		auto &body
		:
		bodies_
	)
		body.second =
			body_status::marked_for_deletion;
}

sanguis::collision::world::body_exit_container
sanguis::collision::impl::world::simple::ghost::post_update_bodies()
{
	sanguis::collision::world::body_exit_container result;

	fcppt::algorithm::map_iteration(
		bodies_,
		[
			this,
			&result
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
				result.push_back(
					sanguis::collision::world::body_exit(
						_element.first.get().body_base(),
						ghost_base_
					)
				);

				return
					fcppt::algorithm::update_action::remove;
			}

			return
				fcppt::algorithm::update_action::keep;
		}
	);

	return
		result;
}

sanguis::collision::world::optional_body_enter
sanguis::collision::impl::world::simple::ghost::update_near_body(
	sanguis::collision::impl::world::simple::body const &_body
)
{
	return
		sanguis::collision::impl::collides(
			sanguis::collision::impl::world::make_circle(
				_body
			),
			sanguis::collision::impl::world::make_circle(
				*this
			)
		)
		?
			fcppt::maybe(
				fcppt::container::find_opt_mapped(
					bodies_,
					fcppt::make_cref(
						_body
					)
				),
				[
					this,
					&_body
				]
				{
					bodies_.insert(
						std::make_pair(
							fcppt::make_cref(
								_body
							),
							body_status::normal
						)
					);

					return
						sanguis::collision::world::optional_body_enter(
							sanguis::collision::world::body_enter(
								_body.body_base(),
								ghost_base_,
								sanguis::collision::world::created{
									false
								}
							)
						);
				},
				[](
					body_status &_status
				)
				{
					_status =
						body_status::normal;

					return
						sanguis::collision::world::optional_body_enter();
				}
			)
		:
			sanguis::collision::world::optional_body_enter()
		;
}

sanguis::collision::world::optional_body_enter
sanguis::collision::impl::world::simple::ghost::new_body(
	sanguis::collision::impl::world::simple::body const &_body,
	sanguis::collision::world::created const _created
)
{
	if(
		!sanguis::collision::impl::collides(
			sanguis::collision::impl::world::make_circle(
				_body
			),
			sanguis::collision::impl::world::make_circle(
				*this
			)
		)
	)
		return
			sanguis::collision::world::optional_body_enter();

	FCPPT_ASSERT_ERROR(
		bodies_.insert(
			std::make_pair(
				fcppt::make_cref(
					_body
				),
				body_status::normal
			)
		).second
	);

	return
		sanguis::collision::world::optional_body_enter(
			sanguis::collision::world::body_enter{
				_body.body_base(),
				ghost_base_,
				_created
			}
		);
}

sanguis::collision::world::optional_body_exit
sanguis::collision::impl::world::simple::ghost::remove_body(
	sanguis::collision::impl::world::simple::body const &_body
)
{
	return
		fcppt::optional_map(
			fcppt::container::find_opt_iterator(
				bodies_,
				fcppt::make_cref(
					_body
				)
			),
			[
				this,
				&_body
			](
				sanguis::collision::impl::world::simple::ghost::body_map::iterator const _it
			){
				bodies_.erase(
					_it
				);

				return
					sanguis::collision::world::body_exit(
						_body.body_base(),
						ghost_base_
					);
			}
		);
}

void
sanguis::collision::impl::world::simple::ghost::body_destroyed(
	sanguis::collision::impl::world::simple::body const &_body
)
{
	bodies_.erase(
		fcppt::make_cref(
			_body
		)
	);
}
