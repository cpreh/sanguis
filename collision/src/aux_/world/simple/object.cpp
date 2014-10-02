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


#include <sanguis/collision/aux_/world/body_ghost_group_relation.hpp>
#include <sanguis/collision/aux_/world/body_group_relation.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/runtime_enum.hpp>
#include <fcppt/algorithm/array_fold_static.hpp>
#include <fcppt/container/array_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cstddef>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	sanguis::collision::world::body_group Group
>
using
body_relations
=
typename
boost::mpl::fold<
	sanguis::collision::aux_::world::body_group_relation,
	boost::mpl::vector0<>,
	boost::mpl::if_<
		boost::is_same<
			boost::mpl::first<
				boost::mpl::_2
			>,
			std::integral_constant<
				sanguis::collision::world::body_group,
				Group
			>
		>,
		boost::mpl::push_back<
			boost::mpl::_1,
			boost::mpl::second<
				boost::mpl::_2
			>
		>,
		boost::mpl::if_<
			boost::is_same<
				boost::mpl::second<
					boost::mpl::_2
				>,
				std::integral_constant<
					sanguis::collision::world::body_group,
					Group
				>
			>,
			boost::mpl::push_back<
				boost::mpl::_1,
				boost::mpl::first<
					boost::mpl::_2
				>
			>,
			boost::mpl::_1
		>
	>
>::type;

template<
	sanguis::collision::world::body_group Group
>
using
body_ghost_relations
=
typename
boost::mpl::fold<
	sanguis::collision::aux_::world::body_ghost_group_relation,
	boost::mpl::vector0<>,
	boost::mpl::if_<
		boost::is_same<
			std::integral_constant<
				sanguis::collision::world::body_group,
				Group
			>,
			boost::mpl::first<
				boost::mpl::_2
			>
		>,
		boost::mpl::push_back<
			boost::mpl::_1,
			boost::mpl::second<
				boost::mpl::_2
			>
		>,
		boost::mpl::_1
	>
>::type;

template<
	sanguis::collision::world::ghost_group Group
>
using
ghost_body_relations
=
typename
boost::mpl::fold<
	sanguis::collision::aux_::world::body_ghost_group_relation,
	boost::mpl::vector0<>,
	boost::mpl::if_<
		boost::is_same<
			std::integral_constant<
				sanguis::collision::world::ghost_group,
				Group
			>,
			boost::mpl::second<
				boost::mpl::_2
			>
		>,
		boost::mpl::push_back<
			boost::mpl::_1,
			boost::mpl::first<
				boost::mpl::_2
			>
		>,
		boost::mpl::_1
	>
>::type;

template<
	sanguis::collision::world::body_group Group
>
using
body_array_type
=
std::array<
	sanguis::collision::world::body_group,
	boost::mpl::size<
		body_relations<
			Group
		>
	>::value
>;

template<
	sanguis::collision::world::body_group Group
>
using
body_ghost_array_type
=
std::array<
	sanguis::collision::world::ghost_group,
	boost::mpl::size<
		body_ghost_relations<
			Group
		>
	>::value
>;

template<
	sanguis::collision::world::ghost_group Group
>
using
ghost_body_array_type
=
std::array<
	sanguis::collision::world::body_group,
	boost::mpl::size<
		ghost_body_relations<
			Group
		>
	>::value
>;

template<
	sanguis::collision::world::body_group Group
>
struct make_body_group
{
	template<
		std::size_t Index
	>
	sanguis::collision::world::body_group
	operator()() const
	{
		return
			boost::mpl::at_c<
				body_relations<
					Group
				>,
				Index
			>::type::value;
	}
};

template<
	sanguis::collision::world::body_group Group
>
struct make_body_ghost_group
{
	template<
		std::size_t Index
	>
	sanguis::collision::world::ghost_group
	operator()() const
	{
		return
			boost::mpl::at_c<
				body_ghost_relations<
					Group
				>,
				Index
			>::type::value;
	}
};

template<
	sanguis::collision::world::ghost_group Group
>
struct make_ghost_body_group
{
	template<
		std::size_t Index
	>
	sanguis::collision::world::body_group
	operator()() const
	{
		return
			boost::mpl::at_c<
				ghost_body_relations<
					Group
				>,
				Index
			>::type::value;
	}
};

template<
	sanguis::collision::world::body_group Group
>
body_array_type<
	Group
>
make_paired_array()
{
	return
		fcppt::algorithm::array_fold_static<
			body_array_type<
				Group
			>
		>(
			make_body_group<
				Group
			>()
		);
}

template<
	sanguis::collision::world::body_group Group
>
body_ghost_array_type<
	Group
>
make_body_ghost_array()
{
	return
		fcppt::algorithm::array_fold_static<
			body_ghost_array_type<
				Group
			>
		>(
			make_body_ghost_group<
				Group
			>()
		);
}

template<
	sanguis::collision::world::ghost_group Group
>
ghost_body_array_type<
	Group
>
make_ghost_body_array()
{
	return
		fcppt::algorithm::array_fold_static<
			ghost_body_array_type<
				Group
			>
		>(
			make_ghost_body_group<
				Group
			>()
		);
}

static_assert(
	fcppt::container::array_size<
		body_array_type<
			sanguis::collision::world::body_group::player
		>
	>::value
	==
	2,
	"player"
);

static_assert(
	fcppt::container::array_size<
		body_array_type<
			sanguis::collision::world::body_group::enemy
		>
	>::value
	==
	1,
	"enemy"
);

static_assert(
	fcppt::container::array_size<
		ghost_body_array_type<
			sanguis::collision::world::ghost_group::player_sight
		>
	>::value
	==
	6,
	"sight range"
);

static_assert(
	boost::mpl::at_c<
		body_relations<
			sanguis::collision::world::body_group::enemy
		>,
		0
	>::type::value
	==
	sanguis::collision::world::body_group::projectile_player,
	"paired"
);


class body_body_collision
{
	FCPPT_NONASSIGNABLE(
		body_body_collision
	);
public:
	body_body_collision(
		sanguis::collision::world::body_collision_callback const &_callback,
		sanguis::collision::aux_::world::simple::object::body_set_array const &_bodies,
		sanguis::collision::aux_::world::simple::object::body_list_grid_array const &_body_list_grids,
		sanguis::creator::dim const _grid_size
	)
	:
		callback_(
			_callback
		),
		bodies_(
			_bodies
		),
		body_list_grids_(
			_body_list_grids
		),
		grid_size_(
			_grid_size
		)
	{
	}

	typedef
	void
	result_type;

	template<
		typename Group
	>
	result_type
	operator()(
		Group
	) const
	{
		auto const paired_groups(
			make_paired_array<
				Group::value
			>()
		);

		for(
			auto const body1
			:
			bodies_[
				Group::value
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
							callback_(
								body1->body_base(),
								body2.body_base()
							);
			}
		}
	}
private:
	sanguis::collision::world::body_collision_callback const callback_;

	sanguis::collision::aux_::world::simple::object::body_set_array const &bodies_;

	sanguis::collision::aux_::world::simple::object::body_list_grid_array const &body_list_grids_;

	sanguis::creator::dim const grid_size_;
};

class ghost_body_collision
{
	FCPPT_NONASSIGNABLE(
		ghost_body_collision
	);
public:
	ghost_body_collision(
		sanguis::collision::aux_::world::simple::object::ghost_set_array const &_ghost_sets,
		sanguis::collision::aux_::world::simple::object::body_list_grid_array const &_body_list_grids
	)
	:
		ghost_sets_(
			_ghost_sets
		),
		body_list_grids_(
			_body_list_grids
		)
	{
	}

	typedef
	void
	result_type;

	template<
		typename Group
	>
	result_type
	operator()(
		Group
	) const
	{
		auto const paired_groups(
			make_ghost_body_array<
				Group::value
			>()
		);

		for(
			sanguis::collision::aux_::world::simple::ghost *const ghost
			:
			ghost_sets_[
				Group::value
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
private:
	sanguis::collision::aux_::world::simple::object::ghost_set_array const &ghost_sets_;

	sanguis::collision::aux_::world::simple::object::body_list_grid_array const &body_list_grids_;
};

class activate_body_function
{
	FCPPT_NONASSIGNABLE(
		activate_body_function
	);
public:
	activate_body_function(
		sanguis::collision::aux_::world::simple::body &_body,
		sanguis::collision::aux_::world::simple::object::ghost_set_array const &_ghost_sets
	)
	:
		body_(
			_body
		),
		ghost_sets_(
			_ghost_sets
		)
	{
	}

	typedef
	void
	result_type;

	template<
		typename Group
	>
	result_type
	operator()(
		Group
	) const
	{
		for(
			sanguis::collision::world::ghost_group const ghost_group
			:
			make_body_ghost_array<
				Group::value
			>()
		)
			for(
				auto const ghost
				:
				ghost_sets_[
					ghost_group
				]
			)
				ghost->new_body(
					body_
				);
	}
private:
	sanguis::collision::aux_::world::simple::body &body_;

	sanguis::collision::aux_::world::simple::object::ghost_set_array const &ghost_sets_;
};

class remove_body_function
{
	FCPPT_NONASSIGNABLE(
		remove_body_function
	);
public:
	remove_body_function(
		sanguis::collision::aux_::world::simple::body &_body,
		sanguis::collision::aux_::world::simple::object::ghost_set_array const &_ghost_sets
	)
	:
		body_(
			_body
		),
		ghost_sets_(
			_ghost_sets
		)
	{
	}

	typedef
	void
	result_type;

	template<
		typename Group
	>
	result_type
	operator()(
		Group
	) const
	{
		for(
			sanguis::collision::world::ghost_group const ghost_group
			:
			make_body_ghost_array<
				Group::value
			>()
		)
			for(
				auto const ghost
				:
				ghost_sets_[
					ghost_group
				]
			)
				ghost->remove_body(
					body_
				);
	}
private:
	sanguis::collision::aux_::world::simple::body &body_;

	sanguis::collision::aux_::world::simple::object::ghost_set_array const &ghost_sets_;
};

class create_ghost_function
{
public:
	create_ghost_function(
		sanguis::collision::aux_::world::simple::ghost &_ghost,
		sanguis::collision::aux_::world::simple::object::body_set_array const &_body_sets
	)
	:
		ghost_(
			_ghost
		),
		body_sets_(
			_body_sets
		)
	{
	}

	typedef
	void
	result_type;

	template<
		typename Group
	>
	result_type
	operator()(
		Group
	) const
	{
		for(
			sanguis::collision::world::body_group body_group
			:
			make_ghost_body_array<
				Group::value
			>()
		)
			for(
				auto const body
				:
				body_sets_[
					body_group
				]
			)
				ghost_.new_body(
					*body
				);
	}
private:
	sanguis::collision::aux_::world::simple::ghost &ghost_;

	sanguis::collision::aux_::world::simple::object::body_set_array const &body_sets_;
};

}

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

	fcppt::runtime_enum(
		body.collision_group(),
		activate_body_function(
			body,
			ghost_sets_
		)
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

	fcppt::runtime_enum(
		result->collision_group(),
		create_ghost_function(
			*result,
			body_sets_
		)
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
		fcppt::runtime_enum(
			body_group,
			body_body_collision(
				body_collision_callback_,
				body_sets_,
				body_list_grids_,
				grid_size_
			)
		);

	for(
		auto const ghost_group
		:
		fcppt::make_enum_range<
			sanguis::collision::world::ghost_group
		>()
	)
		fcppt::runtime_enum(
			ghost_group,
			ghost_body_collision(
				ghost_sets_,
				body_list_grids_
			)
		);
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

	fcppt::runtime_enum(
		_body.collision_group(),
		remove_body_function(
			_body,
			ghost_sets_
		)
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
