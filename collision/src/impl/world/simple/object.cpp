#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/collision/impl/world/body_groups_for_body_group.hpp>
#include <sanguis/collision/impl/world/body_groups_for_ghost_group.hpp>
#include <sanguis/collision/impl/world/ghost_groups_for_body_group.hpp>
#include <sanguis/collision/impl/world/simple/body.hpp>
#include <sanguis/collision/impl/world/simple/body_list.hpp>
#include <sanguis/collision/impl/world/simple/body_list_grid.hpp>
#include <sanguis/collision/impl/world/simple/body_remove_callback.hpp>
#include <sanguis/collision/impl/world/simple/body_unique_ptr.hpp>
#include <sanguis/collision/impl/world/simple/collides.hpp>
#include <sanguis/collision/impl/world/simple/for_all_body_neighbors.hpp>
#include <sanguis/collision/impl/world/simple/ghost.hpp>
#include <sanguis/collision/impl/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/impl/world/simple/ghost_result.hpp>
#include <sanguis/collision/impl/world/simple/ghost_unique_ptr.hpp>
#include <sanguis/collision/impl/world/simple/grid_position.hpp>
#include <sanguis/collision/impl/world/simple/object.hpp>
#include <sanguis/collision/impl/world/simple/push_near.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_collision_container.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/optional_body_enter.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/collision/world/update_result.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/reference_wrapper_comparison.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/algorithm/array_init_move.hpp>
#include <fcppt/algorithm/map_concat.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/container/enum_array_impl.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/clamped_min.hpp>
#include <fcppt/container/grid/clamped_sup_signed.hpp>
#include <fcppt/container/grid/make_pos_ref_range_start_end.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::impl::world::simple::object::object(
	sanguis::collision::world::parameters const &_parameters
)
:
	sanguis::collision::world::object(),
	grid_{
		_parameters.grid()
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
					sanguis::collision::impl::world::simple::body_list_grid(
						_parameters.grid().size(),
						[](
							sanguis::collision::impl::world::simple::body_list_grid::pos
						){
							return
								sanguis::collision::impl::world::simple::body_list();
						}
					);
			}
		)
	}
{
}

sanguis::collision::impl::world::simple::object::~object()
{
}

sanguis::collision::world::body_unique_ptr
sanguis::collision::impl::world::simple::object::create_body(
	sanguis::collision::world::body_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::collision::world::body
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::collision::impl::world::simple::body
			>(
				_parameters,
				sanguis::collision::impl::world::simple::body_remove_callback(
					std::bind(
						&sanguis::collision::impl::world::simple::object::remove_body,
						this,
						std::placeholders::_1
					)
				),
				sanguis::collision::impl::world::simple::body_move_callback(
					std::bind(
						&sanguis::collision::impl::world::simple::object::move_body,
						this,
						std::placeholders::_1
					)
				)
			)
		);
}

sanguis::collision::world::body_enter_container
sanguis::collision::impl::world::simple::object::activate_body(
	sanguis::collision::world::body &_body,
	sanguis::collision::world::created const _created
)
{
	sanguis::collision::impl::world::simple::body &body(
		fcppt::cast::static_downcast<
			sanguis::collision::impl::world::simple::body &
		>(
			_body
		)
	);

	FCPPT_ASSERT_ERROR(
		body_sets_[
			body.collision_group()
		].insert(
			fcppt::make_ref(
				body
			)
		).second
	);


	this->move_body(
		body
	);

	return
		fcppt::algorithm::map_concat<
			sanguis::collision::world::body_enter_container
		>(
			sanguis::collision::impl::world::ghost_groups_for_body_group(
				body.collision_group()
			),
			[
				_created,
				this,
				&body
			](
				sanguis::collision::world::ghost_group const _ghost_group
			)
			{
				return
					fcppt::algorithm::map_optional<
						sanguis::collision::world::body_enter_container
					>(
						ghost_sets_[
							_ghost_group
						],
						[
							_created,
							&body
						](
							ghost_reference const _ghost
						)
						{
							return
								_ghost.get().new_body(
									body,
									_created
								);
						}
					);
			}
		);
}

sanguis::collision::world::body_exit_container
sanguis::collision::impl::world::simple::object::deactivate_body(
	sanguis::collision::world::body &_body
)
{
	sanguis::collision::impl::world::simple::body &body(
		fcppt::cast::static_downcast<
			sanguis::collision::impl::world::simple::body &
		>(
			_body
		)
	);

	FCPPT_ASSERT_ERROR(
		body_sets_[
			body.collision_group()
		].erase(
			fcppt::make_ref(
				body
			)
		)
		== 1u
	);

	return
		fcppt::algorithm::map_concat<
			sanguis::collision::world::body_exit_container
		>(
			sanguis::collision::impl::world::ghost_groups_for_body_group(
				body.collision_group()
			),
			[
				this,
				&body
			](
				sanguis::collision::world::ghost_group const _ghost_group
			)
			{
				return
					fcppt::algorithm::map_optional<
						sanguis::collision::world::body_exit_container
					>(
						ghost_sets_[
							_ghost_group
						],
						[
							&body
						](
							ghost_reference const _ghost
						)
						{
							return
								_ghost.get().remove_body(
									body
								);
						}
					);
			}
		);
}

sanguis::collision::world::ghost_unique_ptr
sanguis::collision::impl::world::simple::object::create_ghost(
	sanguis::collision::world::ghost_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::collision::world::ghost
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::collision::impl::world::simple::ghost
			>(
				_parameters,
				sanguis::collision::impl::world::simple::ghost_remove_callback(
					std::bind(
						&sanguis::collision::impl::world::simple::object::remove_ghost,
						this,
						std::placeholders::_1
					)
				)
			)
		);
}

sanguis::collision::world::body_enter_container
sanguis::collision::impl::world::simple::object::activate_ghost(
	sanguis::collision::world::ghost &_ghost
)
{
	sanguis::collision::impl::world::simple::ghost &ghost(
		fcppt::cast::static_downcast<
			sanguis::collision::impl::world::simple::ghost &
		>(
			_ghost
		)
	);

	FCPPT_ASSERT_ERROR(
		ghost_sets_[
			ghost.collision_group()
		].insert(
			fcppt::make_ref(
				ghost
			)
		).second
	);

	return
		fcppt::algorithm::map_concat<
			sanguis::collision::world::body_enter_container
		>(
			sanguis::collision::impl::world::body_groups_for_ghost_group(
				ghost.collision_group()
			),
			[
				this,
				&ghost
			](
				sanguis::collision::world::body_group const _body_group
			)
			{
				return
					fcppt::algorithm::map_optional<
						sanguis::collision::world::body_enter_container
					>(
						body_sets_[
							_body_group
						],
						[
							&ghost
						](
							body_reference const _body
						)
						{
							return
								ghost.new_body(
									_body.get(),
									sanguis::collision::world::created{
										false
									}
								);
						}
					);
			}
		);
}

sanguis::collision::world::body_exit_container
sanguis::collision::impl::world::simple::object::deactivate_ghost(
	sanguis::collision::world::ghost &_ghost
)
{
	sanguis::collision::impl::world::simple::ghost &ghost(
		fcppt::cast::static_downcast<
			sanguis::collision::impl::world::simple::ghost &
		>(
			_ghost
		)
	);

	FCPPT_ASSERT_ERROR(
		ghost_sets_[
			ghost.collision_group()
		].erase(
			fcppt::make_ref(
				ghost
			)
		)
		== 1u
	);

	return
		fcppt::algorithm::map_concat<
			sanguis::collision::world::body_exit_container
		>(
			sanguis::collision::impl::world::body_groups_for_ghost_group(
				ghost.collision_group()
			),
			[
				this,
				&ghost
			](
				sanguis::collision::world::body_group const _body_group
			)
			{
				return
					fcppt::algorithm::map_optional<
						sanguis::collision::world::body_exit_container
					>(
						body_sets_[
							_body_group
						],
						[
							&ghost
						](
							body_reference const _body
						)
						{
							return
								ghost.remove_body(
									_body.get()
								);
						}
					);
			}
		);
}

sanguis::collision::world::update_result
sanguis::collision::impl::world::simple::object::update(
	sanguis::collision::duration const _duration
)
{
	this->move_bodies(
		_duration
	);

	sanguis::collision::impl::world::simple::ghost_result ghost_result(
		this->update_ghosts()
	);

	return
		sanguis::collision::world::update_result(
			ghost_result.release_body_enter(),
			ghost_result.release_body_exit(),
			this->body_collisions()
		);
}

void
sanguis::collision::impl::world::simple::object::move_bodies(
	sanguis::collision::duration const _duration
)
{
	for(
		body_set const &body_list
		:
		body_sets_
	)
		for(
			body_reference const body_ref
			:
			body_list
		)
		{
			sanguis::collision::impl::world::simple::body &body1(
				body_ref.get()
			);

			if(
				body1.collision_group()
				==
				sanguis::collision::world::body_group::enemy
			)
				sanguis::collision::impl::world::simple::for_all_body_neighbors(
					sanguis::collision::impl::world::simple::grid_position(
						body1.center()
					),
					grid_.size(),
					[
						&body1,
						this
					](
						sanguis::creator::pos const _pos2
					)
					{
						for(
							auto const &body2
							:
							body_list_grids_[
								body1.collision_group()
							][
								_pos2
							]
						)
							fcppt::maybe_void(
								sanguis::collision::impl::world::simple::push_near(
									body1,
									body2
								),
								[
									&body1
								](
									sanguis::collision::result const &_result
								)
								{
									body1.push(
										_result
									);
								}
							);
					}
				);

			body1.move(
				sanguis::collision::test_move(
					body1.center(),
					body1.radius(),
					body1.speed(),
					_duration,
					grid_
				),
				_duration
			);

			this->move_body(
				body1
			);
		}
}

sanguis::collision::world::body_collision_container
sanguis::collision::impl::world::simple::object::body_collisions() const
{
	sanguis::collision::world::body_collision_container result;

	for(
		auto const body_group
		:
		fcppt::make_enum_range<
			sanguis::collision::world::body_group
		>()
	)
	{
		sanguis::collision::impl::world::body_group_container const &paired_groups(
			sanguis::collision::impl::world::body_groups_for_body_group(
				body_group
			)
		);

		for(
			body_reference const body1
			:
			body_sets_[
				body_group
			]
		)
			sanguis::collision::impl::world::simple::for_all_body_neighbors(
				sanguis::collision::impl::world::simple::grid_position(
					body1.get().center()
				),
				grid_.size(),
				[
					body1,
					&paired_groups,
					&result,
					this
				](
					sanguis::creator::pos const _grid_pos2
				)
				{
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
								_grid_pos2
							]
						)
							if(
								sanguis::collision::impl::world::simple::collides(
									body1.get(),
									body2
								)
							)
								result.push_back(
									sanguis::collision::world::body_collision{
										body1.get().body_base(),
										body2.body_base()
									}
								);
				}
			);
	}

	return
		result;
}

sanguis::collision::impl::world::simple::ghost_result
sanguis::collision::impl::world::simple::object::update_ghosts()
{
	sanguis::collision::world::body_enter_container body_enter;

	sanguis::collision::world::body_exit_container body_exit;

	for(
		auto const ghost_group
		:
		fcppt::make_enum_range<
			sanguis::collision::world::ghost_group
		>()
	)
	{
		sanguis::collision::impl::world::body_group_container const &paired_groups(
			sanguis::collision::impl::world::body_groups_for_ghost_group(
				ghost_group
			)
		);

		for(
			ghost_reference const ghost
			:
			ghost_sets_[
				ghost_group
			]
		)
		{
			ghost.get().pre_update_bodies();

			auto const signed_pos(
				fcppt::math::vector::structure_cast<
					sanguis::creator::signed_pos,
					fcppt::cast::to_signed_fun
				>(
					sanguis::collision::impl::world::simple::grid_position(
						ghost.get().center()
					)
				)
			);

			auto const rounded_radius(
				fcppt::cast::float_to_int<
					sanguis::creator::difference_type
				>(
					std::ceil(
						ghost.get().radius().get()
					)
				)
			);

			for(
				sanguis::collision::world::body_group const body_group
				:
				paired_groups
			)
			{
				sanguis::collision::impl::world::simple::body_list_grid const &grid(
					body_list_grids_[
						body_group
					]
				);

				for(
					auto const grid_entry
					:
					fcppt::container::grid::make_pos_ref_range_start_end(
						grid,
						fcppt::container::grid::clamped_min(
							signed_pos
							-
							rounded_radius
						),
						fcppt::container::grid::clamped_sup_signed(
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
						sanguis::collision::impl::world::simple::body const &body
						:
						grid_entry.value()
					)
						fcppt::maybe_void(
							ghost.get().update_near_body(
								body
							),
							[
								&body_enter
							](
								sanguis::collision::world::body_enter const _enter
							)
							{
								body_enter.push_back(
									_enter
								);
							}
						);
			}

			fcppt::algorithm::append(
				body_exit,
				ghost.get().post_update_bodies()
			);
		}
	}

	return
		sanguis::collision::impl::world::simple::ghost_result(
			std::move(
				body_enter
			),
			std::move(
				body_exit
			)
		);
}

void
sanguis::collision::impl::world::simple::object::remove_body(
	sanguis::collision::impl::world::simple::body &_body
)
{
	if(
		body_sets_[
			_body.collision_group()
		].erase(
			fcppt::make_ref(
				_body
			)
		)
		>
		0
	)
		for(
			sanguis::collision::world::ghost_group const ghost_group
			:
			sanguis::collision::impl::world::ghost_groups_for_body_group(
				_body.collision_group()
			)
		)
			for(
				ghost_reference const ghost
				:
				ghost_sets_[
					ghost_group
				]
			)
				ghost.get().body_destroyed(
					_body
				);
}

void
sanguis::collision::impl::world::simple::object::remove_ghost(
	sanguis::collision::impl::world::simple::ghost &_ghost
)
{
	ghost_sets_[
		_ghost.collision_group()
	].erase(
		fcppt::make_ref(
			_ghost
		)
	);
}

void
sanguis::collision::impl::world::simple::object::move_body(
	sanguis::collision::impl::world::simple::body &_body
)
{
	_body.unlink();

	fcppt::maybe_void(
		fcppt::container::grid::at_optional(
			body_list_grids_[
				_body.collision_group()
			],
			sanguis::collision::impl::world::simple::grid_position(
				_body.center()
			)
		),
		[
			&_body
		](
			sanguis::collision::impl::world::simple::body_list &_bodies
		)
		{
			_bodies.push_back(
				_body
			);
		}
	);
}
