#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/aux_/world/simple/body.hpp>
#include <sanguis/collision/aux_/world/simple/body_list_grid.hpp>
#include <sanguis/collision/aux_/world/simple/body_remove_callback.hpp>
#include <sanguis/collision/aux_/world/simple/body_unique_ptr.hpp>
#include <sanguis/collision/aux_/world/simple/collides.hpp>
#include <sanguis/collision/aux_/world/simple/ghost.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/aux_/world/simple/ghost_unique_ptr.hpp>
#include <sanguis/collision/aux_/world/simple/grid_position.hpp>
#include <sanguis/collision/aux_/world/simple/groups_collide.hpp>
#include <sanguis/collision/aux_/world/simple/object.hpp>
#include <sanguis/collision/world/body_fwd.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/array_init_move.hpp>
#include <fcppt/algorithm/array_push_back.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/int_to_enum.hpp>
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
#include <boost/range/irange.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <cstddef>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


// TODO: With C++14 we can have polymorphic lambdas and return type deduction
#define SANGUIS_COLLISION_FILTER_BY_GROUP(\
	_name,\
	_type\
)\
auto const _name(\
	[](\
		_type &_array,\
		sanguis::collision::world::group const _group\
	)\
	{\
		return \
			boost::adaptors::transform(\
				boost::adaptors::filter(\
					boost::irange(\
						fcppt::literal<\
							std::size_t\
						>(\
							0 \
						),\
						fcppt::enum_size<\
							sanguis::collision::world::group\
						>::value\
					),\
					[\
						_group\
					](\
						int const _group2\
					)\
					{\
						return \
							sanguis::collision::aux_::world::simple::groups_collide(\
								_group,\
								fcppt::cast::int_to_enum<\
									sanguis::collision::world::group\
								>(\
									_group2\
								)\
							);\
					}\
				),\
				[\
					&_array\
				](\
					int const _index\
				)\
				-> _type::reference \
				{\
					return \
						_array[\
							fcppt::cast::int_to_enum<\
								sanguis::collision::world::group\
							>(\
								_index\
							)\
						];\
				}\
			); \
	}\
)

namespace
{

SANGUIS_COLLISION_FILTER_BY_GROUP(
	filter_bodies,
	sanguis::collision::aux_::world::simple::object::body_set_array
);

SANGUIS_COLLISION_FILTER_BY_GROUP(
	filter_ghosts,
	sanguis::collision::aux_::world::simple::object::ghost_set_array
);

SANGUIS_COLLISION_FILTER_BY_GROUP(
	filter_body_grids,
	sanguis::collision::aux_::world::simple::object::body_list_grid_array
);

}

sanguis::collision::aux_::world::simple::object::object(
	sanguis::collision::world::parameters const &_parameters
)
:
	sanguis::collision::world::object(),
	body_collision_callback_(
		_parameters.body_collision_callback()
	),
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
		auto const &ghost_list
		:
		filter_ghosts(
			ghost_sets_,
			body.collision_group()
		)
	)
		for(
			auto const ghost
			:
			ghost_list
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
		auto const body_list
		:
		filter_bodies(
			body_sets_,
			result->collision_group()
		)
	)
		for(
			auto const body
			:
			body_list
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
		auto &body_list
		:
		body_sets_
	)
		for(
			auto const body1
			:
			body_list
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
				for(
					auto const &grid
					:
					filter_body_grids(
						body_list_grids_,
						body1->collision_group()
					)
				)
					if(
						fcppt::container::grid::in_range(
							grid,
							grid_pos2
						)
					)
						for(
							auto const &body2
							:
							grid[
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
		ghost_set const &ghost_list
		:
		ghost_sets_
	)
		for(
			sanguis::collision::aux_::world::simple::ghost *const ghost
			:
			ghost_list
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
				sanguis::collision::aux_::world::simple::body_list_grid const &grid
				:
				filter_body_grids(
					body_list_grids_,
					ghost->collision_group()
				)
			)
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

			ghost->post_update_bodies();
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
		auto const &ghost_list
		:
		filter_ghosts(
			ghost_sets_,
			_body.collision_group()
		)
	)
		for(
			auto const ghost
			:
			ghost_list
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
