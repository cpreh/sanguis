#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/aux_/world/simple/body.hpp>
#include <sanguis/collision/aux_/world/simple/body_remove_callback.hpp>
#include <sanguis/collision/aux_/world/simple/body_unique_ptr.hpp>
#include <sanguis/collision/aux_/world/simple/collides.hpp>
#include <sanguis/collision/aux_/world/simple/ghost.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_unique_ptr.hpp>
#include <sanguis/collision/aux_/world/simple/grid_position.hpp>
#include <sanguis/collision/aux_/world/simple/object.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/array_push_back.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/container/grid/clamp_signed_pos.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/container/grid/make_pos_range_start_end.hpp>
#include <fcppt/container/grid/moore_neighbors.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::aux_::world::simple::object::object(
	sanguis::collision::world::parameters const &_parameters
)
:
	sanguis::collision::world::object(),
	body_collision_callback_(
		_parameters.body_collision_callback()
	),
	bodies_(),
	ghosts_(),
	body_list_grid_(
		_parameters.grid_size()
	)
{
}

sanguis::collision::aux_::world::simple::object::~object()
{
}

sanguis::collision::world::body_unique_ptr
sanguis::collision::aux_::world::simple::object::create_body(
	sanguis::collision::world::body_parameters const &_parameters
)
{
	sanguis::collision::aux_::world::simple::body_unique_ptr result(
		fcppt::make_unique_ptr<
			sanguis::collision::aux_::world::simple::body
		>(
			_parameters,
			sanguis::collision::aux_::world::simple::body_remove_callback(
				std::bind(
					&sanguis::collision::aux_::world::simple::object::remove_body,
					this,
					std::placeholders::_1
				)
			),
			sanguis::collision::aux_::world::simple::body_move_callback(
				std::bind(
					&sanguis::collision::aux_::world::simple::object::move_body,
					this,
					std::placeholders::_1
				)
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		bodies_.insert(
			result.get()
		).second
	);

	return
		std::move(
			result
		);
}

void
sanguis::collision::aux_::world::simple::object::activate_body(
	sanguis::collision::world::body &_body
)
{
	sanguis::collision::aux_::world::simple::body &body(
		fcppt::cast::static_downcast<
			sanguis::collision::aux_::world::simple::body &
		>(
			_body
		)
	);

	this->move_body(
		body
	);

	for(
		auto ghost
		:
		ghosts_
	)
		ghost->new_body(
			body
		);
}

sanguis::collision::world::ghost_unique_ptr
sanguis::collision::aux_::world::simple::object::create_ghost(
	sanguis::collision::world::ghost_parameters const &_parameters
)
{
	sanguis::collision::aux_::world::simple::ghost_unique_ptr result(
		fcppt::make_unique_ptr<
			sanguis::collision::aux_::world::simple::ghost
		>(
			_parameters,
			sanguis::collision::aux_::world::simple::ghost_remove_callback(
				std::bind(
					&sanguis::collision::aux_::world::simple::object::remove_ghost,
					this,
					std::placeholders::_1
				)
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		ghosts_.insert(
			result.get()
		).second
	);

	for(
		auto const body
		:
		bodies_
	)
		result->new_body(
			*body
		);

	return
		std::move(
			result
		);
}

void
sanguis::collision::aux_::world::simple::object::update(
	sanguis::collision::duration const _duration
)
{
	for(
		auto body
		:
		bodies_
	)
	{
		body->move(
			sanguis::collision::center(
				body->center().get()
				+
				body->speed().get()
				*
				_duration.count()
			)
		);

		this->move_body(
			*body
		);
	}

	for(
		auto const body1
		:
		bodies_
	)
	{
		sanguis::creator::pos const body1_pos(
			sanguis::collision::aux_::world::simple::grid_position(
				body1->center()
			)
		);

		for(
			auto const grid_pos2
			:
			fcppt::algorithm::array_push_back(
				fcppt::container::grid::moore_neighbors(
					body1_pos
				),
				body1_pos
			)
		)
			if(
				fcppt::container::grid::in_range(
					body_list_grid_,
					grid_pos2
				)
			)
				for(
					auto const &body2
					:
					body_list_grid_[
						grid_pos2
					]
				)
					if(
						sanguis::collision::aux_::world::simple::collides(
							*body1,
							body2
						)
					)
						body_collision_callback_(
							body1->body_base(),
							body2.body_base()
						);
	}

	for(
		auto const ghost
		:
		ghosts_
	)
	{
		ghost->pre_update_bodies();

		auto const signed_pos(
			fcppt::math::vector::structure_cast<
				sanguis::creator::signed_pos
			>(
				sanguis::collision::aux_::world::simple::grid_position(
					ghost->center()
				)
			)
		);

		auto const rounded_radius(
			fcppt::cast::float_to_int<
				sanguis::creator::difference_type
			>(
				std::ceil(
					ghost->radius().get()
				)
			)
		);

		for(
			auto const grid_entry
			:
			fcppt::container::grid::make_pos_range_start_end(
				body_list_grid_,
				fcppt::container::grid::clamp_signed_pos(
					signed_pos
					-
					rounded_radius,
					body_list_grid_.size()
				),
				fcppt::container::grid::clamp_signed_pos(
					signed_pos
					+
					rounded_radius
					+
					fcppt::literal<
						sanguis::creator::difference_type
					>(
						1
					),
					body_list_grid_.size()
				)
			)
		)
			for(
				auto &body
				:
				grid_entry.value()
			)
				ghost->update_near_body(
					body
				);

		ghost->post_update_bodies();
	}
}

void
sanguis::collision::aux_::world::simple::object::remove_body(
	sanguis::collision::aux_::world::simple::body &_body
)
{
	FCPPT_ASSERT_ERROR(
		bodies_.erase(
			&_body
		)
		== 1u
	);

	for(
		auto const ghost
		:
		ghosts_
	)
		ghost->remove_body(
			_body
		);
}

void
sanguis::collision::aux_::world::simple::object::remove_ghost(
	sanguis::collision::aux_::world::simple::ghost &_ghost
)
{
	FCPPT_ASSERT_ERROR(
		ghosts_.erase(
			&_ghost
		)
		== 1u
	);
}

void
sanguis::collision::aux_::world::simple::object::move_body(
	sanguis::collision::aux_::world::simple::body &_body
)
{
	_body.unlink();

	sanguis::creator::pos const insert_pos(
		sanguis::collision::aux_::world::simple::grid_position(
			_body.center()
		)
	);

	if(
		fcppt::container::grid::in_range(
			body_list_grid_,
			insert_pos
		)
	)
		body_list_grid_[
			insert_pos
		].push_back(
			_body
		);
}
