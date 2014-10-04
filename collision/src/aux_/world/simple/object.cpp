#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/aux_/world/body_groups_for_body_group.hpp>
#include <sanguis/collision/aux_/world/body_groups_for_ghost_group.hpp>
#include <sanguis/collision/aux_/world/ghost_groups_for_body_group.hpp>
#include <sanguis/collision/aux_/world/simple/body.hpp>
#include <sanguis/collision/aux_/world/simple/body_list_grid.hpp>
#include <sanguis/collision/aux_/world/simple/body_remove_callback.hpp>
#include <sanguis/collision/aux_/world/simple/body_unique_ptr.hpp>
#include <sanguis/collision/aux_/world/simple/collides.hpp>
#include <sanguis/collision/aux_/world/simple/ghost.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_unique_ptr.hpp>
#include <sanguis/collision/aux_/world/simple/grid_position.hpp>
#include <sanguis/collision/aux_/world/simple/object.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/array_init_move.hpp>
#include <fcppt/algorithm/array_push_back.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/container/enum_array_impl.hpp>
#include <fcppt/container/grid/clamp_signed_pos.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/container/grid/make_pos_range_start_end.hpp>
#include <fcppt/container/grid/moore_neighbors.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
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
	grid_size_{
		_parameters.grid_size()
	},
	body_sets_(),
	ghost_sets_(),
	body_list_grids_{
		fcppt::algorithm::array_init_move<
			body_list_grid_array::internal
		>(
			[
				&_parameters
			]()
			{
				return
					sanguis::collision::aux_::world::simple::body_list_grid(
						_parameters.grid_size()
					);
			}
		)
	}
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
		body_sets_[
			result->collision_group()
		].insert(
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
		sanguis::collision::world::ghost_group const ghost_group
		:
		sanguis::collision::aux_::world::ghost_groups_for_body_group(
			body.collision_group()
		)
	)
		for(
			auto const ghost
			:
			ghost_sets_[
				ghost_group
			]
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
		ghost_sets_[
			result->collision_group()
		].insert(
			result.get()
		).second
	);

	for(
		sanguis::collision::world::body_group const body_group
		:
		sanguis::collision::aux_::world::body_groups_for_ghost_group(
			result->collision_group()
		)
	)
		for(
			auto const body
			:
			body_sets_[
				body_group
			]
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
		auto &body_list
		:
		body_sets_
	)
		for(
			auto body
			:
			body_list
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
		auto const body_group
		:
		fcppt::make_enum_range<
			sanguis::collision::world::body_group
		>()
	)
	{
		sanguis::collision::aux_::world::body_group_container const &paired_groups(
			sanguis::collision::aux_::world::body_groups_for_body_group(
				body_group
			)
		);

		for(
			auto const body1
			:
			body_sets_[
				body_group
			]
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
			{
				if(
					!fcppt::container::grid::in_range_dim(
						grid_size_,
						grid_pos2
					)
				)
					continue;

				for(
					sanguis::collision::world::body_group const group2
					:
					paired_groups
				)
					for(
						auto const &body2
						:
						body_list_grids_[
							group2
						][
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
		}
	}

	for(
		auto const ghost_group
		:
		fcppt::make_enum_range<
			sanguis::collision::world::ghost_group
		>()
	)
	{
		sanguis::collision::aux_::world::body_group_container const &paired_groups(
			sanguis::collision::aux_::world::body_groups_for_ghost_group(
				ghost_group
			)
		);

		for(
			sanguis::collision::aux_::world::simple::ghost *const ghost
			:
			ghost_sets_[
				ghost_group
			]
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
				sanguis::collision::world::body_group const body_group
				:
				paired_groups
			)
			{
				sanguis::collision::aux_::world::simple::body_list_grid const &grid(
					body_list_grids_[
						body_group
					]
				);

				for(
					auto const grid_entry
					:
					fcppt::container::grid::make_pos_range_start_end(
						grid,
						fcppt::container::grid::clamp_signed_pos(
							signed_pos
							-
							rounded_radius,
							grid.size()
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
							grid.size()
						)
					)
				)
					for(
						sanguis::collision::aux_::world::simple::body const &body
						:
						grid_entry.value()
					)
						ghost->update_near_body(
							body
						);
			}

			ghost->post_update_bodies();
		}
	}
}

void
sanguis::collision::aux_::world::simple::object::remove_body(
	sanguis::collision::aux_::world::simple::body &_body
)
{
	FCPPT_ASSERT_ERROR(
		body_sets_[
			_body.collision_group()
		].erase(
			&_body
		)
		== 1u
	);

	for(
		sanguis::collision::world::ghost_group const ghost_group
		:
		sanguis::collision::aux_::world::ghost_groups_for_body_group(
			_body.collision_group()
		)
	)
		for(
			auto const ghost
			:
			ghost_sets_[
				ghost_group
			]
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
		ghost_sets_[
			_ghost.collision_group()
		].erase(
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

	sanguis::collision::aux_::world::simple::body_list_grid &grid(
		body_list_grids_[
			_body.collision_group()
		]
	);

	if(
		fcppt::container::grid::in_range(
			grid,
			insert_pos
		)
	)
		grid[
			insert_pos
		].push_back(
			_body
		);
}
