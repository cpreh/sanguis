#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/signed_rect.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/impl/enemy_type_container.hpp>
#include <sanguis/creator/impl/filled_rect.hpp>
#include <sanguis/creator/impl/generate_maze.hpp>
#include <sanguis/creator/impl/interior_range.hpp>
#include <sanguis/creator/impl/maze_to_tile_grid.hpp>
#include <sanguis/creator/impl/parameters.hpp>
#include <sanguis/creator/impl/place_boss.hpp>
#include <sanguis/creator/impl/place_openings.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <sanguis/creator/impl/rect.hpp>
#include <sanguis/creator/impl/region_grid.hpp>
#include <sanguis/creator/impl/region_id.hpp>
#include <sanguis/creator/impl/result.hpp>
#include <sanguis/creator/impl/set_opening_tiles.hpp>
#include <sanguis/creator/impl/generators/rooms.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/uniform_int.hpp>
#include <sanguis/creator/impl/random/uniform_pos.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/fill.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/container/grid/make_pos_ref_range.hpp>
#include <fcppt/container/grid/map.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/container/grid/output.hpp>
#include <fcppt/enum/array.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/to_array.hpp>
#include <fcppt/math/box/center.hpp>
#include <fcppt/math/box/distance.hpp>
#include <fcppt/math/box/intersects.hpp>
#include <fcppt/math/box/object.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/wrapper/make_uniform_container_advanced.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

using signed_rect =
	sanguis::creator::signed_rect;

using pos_type =
	sanguis::creator::signed_pos;

using int_type =
	pos_type::value_type;

using region_grid =
	sanguis::creator::impl::region_grid;

using sanguis::creator::impl::region_id;

auto const
wall_region =
	region_id{
		-1
	};

auto
border_distance =
[](
	signed_rect const _rect,
	sanguis::creator::dim const _size
)
{
	auto const
	level =
		::signed_rect(::signed_rect::vector{0,0},
			fcppt::math::dim::structure_cast<
				::signed_rect::dim,
				fcppt::cast::size_fun
			>(_size));

	using ret_type =
	signed_rect::value_type;

	return
	fcppt::algorithm::fold(
		// they should all have negative distances, so this abs()es
		fcppt::math::to_array(
			-
			fcppt::math::box::distance(
				_rect,
				level
			)
		),
		std::numeric_limits<ret_type>::max(),
		[](ret_type _l, ret_type _r){return std::min(_l, _r);}
	);
};

auto
rect_distance =
[](
	signed_rect a,
	signed_rect b
)
{
	using ret_type =
	signed_rect::value_type;

	return
	fcppt::algorithm::fold(
		fcppt::math::to_array(
			fcppt::math::box::distance(
				a,
				b
			)
		),
		ret_type{0},
		[](ret_type const _l, ret_type const _r){
			return
				std::max(ret_type{0},_l)
				+
				std::max(ret_type{0},_r);
		}
	);
};

using connector =
	std::pair<
		region_id,
		region_id
	>;

using optional_connector =
	fcppt::optional::object<
		connector
	>;

optional_connector
is_possible_connector(
	region_grid grid,
	sanguis::creator::pos p
)
{
	auto const nothing =
		optional_connector{};

	// TODO: optional::map
	if(
		!
		fcppt::container::grid::in_range(
			grid,
			p
		)
		||
		(
			p.x() % 2
			==
			p.y() % 2
		)
		||
		grid.get_unsafe(
			p
		)
		!=
		::wall_region
	)
		return nothing;

	std::map<
		region_id,
		unsigned
	> counts;

	for (
		auto const &n
		:
		fcppt::container::grid::neumann_neighbors(
			p
		)
	)
		fcppt::optional::maybe_void(
			fcppt::optional::copy_value(
				fcppt::container::grid::at_optional(
					grid,
					n
				)
			),
			[&counts](
				sanguis::creator::impl::region_id const _id
			)
			{
				counts[
					_id
				]++;
			}
		);

	// if cell doesn't have exactly two adjacent walls
	if (
			counts[
				::wall_region
			] !=
			2u
	)
		// then we have no result
		return nothing;

	// otherwise determine the first non-wall region
	auto from =
		counts.upper_bound(::wall_region);

	auto const to =
		std::next(from);

	// interior wall, no possible connector
	if (
		to
		==
		std::end(counts)
	)
		return nothing;

	auto const from_region = from->first;
	auto const to_region = to->first;

	// must be an exterior wall, return a possible connector
	return
		optional_connector{
			from_region < to_region ?
			std::make_pair(
				from_region,
				to_region
			)
			:
			std::make_pair(
				to_region,
				from_region
			)
		};
}

}

sanguis::creator::impl::result
sanguis::creator::impl::generators::rooms(
	sanguis::creator::impl::parameters const &_parameters
)
{
	// actual size of the level will be 2x+1 this
	sanguis::creator::grid::dim const size{
		31u,
		31u
	};

	sanguis::creator::impl::reachable_grid
	raw_grid{
		size,
		sanguis::creator::impl::reachable{false}
	};

	std::vector<
		::signed_rect
	>
	rects;

	// 1. generate a bunch of non-overlapping rooms on maze-compatible coords

	auto const max_room_size =
		sanguis::creator::grid::size_type{
			4u
		};

	auto rand_pos =
		sanguis::creator::impl::random::uniform_pos{
			_parameters.randgen(),
			size
			-
			fcppt::math::dim::fill<
				sanguis::creator::grid::dim
			>(
				2 * max_room_size + 1
			)
		};

	using uniform_size =
		fcppt::random::distribution::basic<
			sanguis::creator::impl::random::uniform_int<
				sanguis::creator::grid::size_type
			>
		>;

	auto random_size(
		fcppt::random::make_variate(
			_parameters.randgen(),
			uniform_size{
				uniform_size::param_type::min{
					1u
				},
				uniform_size::param_type::max{
					max_room_size
				},
			}
		)
	);

	auto random_room_dim =
		[&]()
		{
			auto const w =
				random_size();
			auto const h =
				random_size();
			return sanguis::creator::dim{
				2 * w + 1,
				2 * h + 1
			};
		};

	for (
		::int_type i = 0;
		i < 100; // FIXME: magic number
		++i
	)
	{
		auto const wrong = rand_pos();
		auto const rect =
			fcppt::math::box::structure_cast<
				::signed_rect,
				fcppt::cast::to_signed_fun
			>(
				sanguis::creator::rect{
					(wrong / 2u).get_unsafe() * 2u
					+
					fcppt::math::vector::fill<
						sanguis::creator::pos
					>(
						1u
					),
					random_room_dim()
				}
			);

		// TODO use a find_by here instead
		bool overlaps = false;

		for (
			auto const &other
			:
			rects
		)
			if (
				fcppt::math::box::intersects(
					rect,
					other
				)
			)
			{
				overlaps = true;
				break;
			}

		if (!overlaps)
			rects.push_back(
				rect);
	}

	for (
		auto const &rect
		:
		rects
	)
	{
		sanguis::creator::impl::filled_rect(
			fcppt::math::box::structure_cast<
				sanguis::creator::rect,
				fcppt::cast::size_fun
			>(
				rect
			),
			[
				&raw_grid
			]
			(
				sanguis::creator::pos const _pos
			)
			{
				FCPPT_ASSERT_OPTIONAL_ERROR(
					fcppt::container::grid::at_optional(
						raw_grid,
						_pos
					)
				).get() =
					sanguis::creator::impl::reachable{
						true
					};
			}
		);
	}

	// 2. fill in between space with maze corridors
	// 3. identify connected regions
	auto tmp_result =
		sanguis::creator::impl::generate_maze(
			raw_grid,
			_parameters.randgen()
		);

	// 4. connect the level by adding connector tiles between
	// connected regions

	auto region_grid = tmp_result.grid;

	auto output_grid = [&raw_grid,&log = _parameters.log()](
	){
		FCPPT_LOG_DEBUG(
			log,
			fcppt::log::_
				<<
				fcppt::container::grid::map(
					raw_grid,
					[](
						sanguis::creator::impl::reachable const _reachable
					)
					{
						return
							_reachable.get()
							?
								'.'
							:
								'@'
							;
					}
				)
		);
	};

	auto cur_region =
		region_id{
			tmp_result.next_id
		};

	for (auto &room : rects)
	{
		sanguis::creator::impl::filled_rect(
			fcppt::math::box::structure_cast<
				sanguis::creator::rect,
				fcppt::cast::to_unsigned_fun
			>(
				room
			),
			[
				&region_grid,
				cur_region
			]
			(
				sanguis::creator::pos const p
			)
			{
				FCPPT_ASSERT_OPTIONAL_ERROR(
					fcppt::container::grid::at_optional(
						region_grid,
						p
					)
				).get() =
					cur_region;
			}
		);

		++cur_region;
	}

	output_grid();

	// placing connectors...

	// candidates for connectors between regions
	std::map<
		std::pair<
			region_id,
			region_id
		>,
		std::vector<
			sanguis::creator::pos
		>
	>
	connectors;

	// just the edges of the "region graph"
	std::set<
		std::pair<
			region_id,
			region_id
		>
	>
	edges;

	// look for possible connector cells in the grid,
	// examining each position only once(!)
	for (
		auto const &p
		:
		// no possible connector tiles can be on the
		// edge of the map, so only look for them in the
		// interior
		sanguis::creator::impl::interior_range(
			region_grid
		)
	)
	{
		fcppt::optional::maybe_void(
			// find out if it's a connector candidate...
			is_possible_connector(
				region_grid,
				p.pos()
			),
			// and if so, add it to the set,
			// otherwise do nothing
			[&](
				connector _c
			)
			{
				connectors[
					_c
				].push_back(
					p.pos()
				);

				edges.insert(
					_c
				);
			}
		);
	}

	using uniform_int =
		fcppt::random::distribution::basic<
			sanguis::creator::impl::random::uniform_int<
				region_id
			>
		>;

	auto random_region(
		fcppt::random::make_variate(
			_parameters.randgen(),
			uniform_int{
				uniform_int::param_type::min{
					0
				},
				uniform_int::param_type::max{
					cur_region - 1
				},
			}
		)
	);

	// build minimum spanning tree
	std::set<
		region_id
	> verts{
		random_region()
	};

	std::set<
		std::pair<
			region_id,
			region_id
		>
	> remaining_edges;

	auto find =
		[&verts](
			region_id _v
		)
		{
			return verts.find(_v) != std::end(verts);
		};

	while (
		verts.size() < cur_region
	)
		for (
			auto const &edge
			:
			edges
		)
		{
			if (
				find(edge.first) && !find(edge.second)
			)
			{
				verts.insert(edge.second);
				remaining_edges.insert(edge);
			}
			else if (
				!find(edge.first) && find(edge.second)
			)
			{
				verts.insert(edge.first);
				remaining_edges.insert(edge);
			}
		}

	// TODO: add more edges than strictly necessary
	// for now, the level has no cycles
	// depending on how many remaining edges there are
	for (
		auto const &edge
		:
		remaining_edges
	)
	{
		auto const positions =
			connectors[edge];

		auto random_connector(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::random::wrapper::make_uniform_container_advanced<
					sanguis::creator::impl::random::uniform_int_wrapper
				>(
					positions
				)
			)
		);

		auto const passage =
			random_connector(
				_parameters.randgen()
			);

		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::grid::at_optional(
				raw_grid,
				passage
			)
		).get() =
			sanguis::creator::impl::reachable{true};
	}

	output_grid();


	// 5. remove dead ends by iteratively deleting (setting to wall) corridor tiles that have 3 wall neighbors
	while (
		[&]()
		{
			bool ret = false;

			fcppt::container::grid::fill(
				region_grid,
				[](sanguis::creator::pos){return 0;}
			);

			for (
				auto const &p
				:
				fcppt::container::grid::make_pos_ref_range(
					region_grid
				)
			)
				for(
					auto const &n
					:
					fcppt::container::grid::neumann_neighbors(
						p.pos()
					)
				)
					fcppt::optional::maybe_void(
						fcppt::container::grid::at_optional(
							region_grid,
							n
						),
						[
							&raw_grid,
							p,
							n
						](
							fcppt::reference<
								sanguis::creator::impl::region_id
							> const _ref
						)
						{
							if(
								FCPPT_ASSERT_OPTIONAL_ERROR(
									fcppt::container::grid::at_optional(
										raw_grid,
										p.pos()
									)
								).get()
								==
								sanguis::creator::impl::reachable{true}
								&&
								FCPPT_ASSERT_OPTIONAL_ERROR(
									fcppt::container::grid::at_optional(
										raw_grid,
										n
									)
								).get()
								==
								sanguis::creator::impl::reachable{true}
							)
								++_ref.get();
						}
					);

			for (
				auto const p
				:
				fcppt::container::grid::make_pos_ref_range(
					raw_grid
				)
			)
			{
				if(
					FCPPT_ASSERT_OPTIONAL_ERROR(
						fcppt::container::grid::at_optional(
							region_grid,
							p.pos()
						)
					).get()
					==
					region_id{1}
				)
				{
					p.value() = sanguis::creator::impl::reachable{false};
					ret = true;
				}
			}

			return ret;
		}()
	);

	output_grid();

	sanguis::creator::grid grid{
		sanguis::creator::impl::maze_to_tile_grid(
			raw_grid,
			1, // scale factor walls
			1, // scale factor space
			sanguis::creator::tile::nothing,
			sanguis::creator::tile::concrete_wall
		)
	};

	sanguis::creator::background_grid bg_grid{
		grid.size(),
		sanguis::creator::background_tile::nothing
	};

	sanguis::creator::impl::filled_rect(
		sanguis::creator::rect{
			fcppt::math::vector::fill<
				sanguis::creator::rect::vector
			>(
				1u
			),
			sanguis::creator::rect::dim{
				grid.size()
				-
				fcppt::math::dim::fill<
					sanguis::creator::rect::dim
				>(
					2u
				)
			}
		},
		[
			&bg_grid
		]
		(
			sanguis::creator::pos const _pos
		)
		{
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::container::grid::at_optional(
					bg_grid,
					_pos
				)
			).get() =
				sanguis::creator::background_tile::asphalt;
		}
	);

	auto const
	rect_center_pos(
		[]
		(
			signed_rect _rect
		)
		{
			return
				fcppt::math::vector::structure_cast<
					sanguis::creator::pos,
					fcppt::cast::to_unsigned_fun
				>
				(
					fcppt::math::box::center(
						_rect)
				);
		}
	);

	std::sort(
		rects.begin(),
		rects.end(),
		[&size](
			::signed_rect const _a,
			::signed_rect const _b
		){
			return border_distance(_a, size) < border_distance(_b, size);
		}
	);

	auto const
	entrance_room =
		rects.front();

	auto const
	exit_room =
	*std::max_element(
		rects.begin(),
		rects.end(),
		[&entrance_room](::signed_rect const _a, ::signed_rect const _b){return rect_distance(_a, entrance_room) < rect_distance(_b, entrance_room);}
	);

	FCPPT_LOG_DEBUG(
		_parameters.log(),
		fcppt::log::_
		<< entrance_room
		<< FCPPT_TEXT(" : ")
		<< exit_room
		<< FCPPT_TEXT("\n")
	);

	FCPPT_ASSERT_ERROR(
		_parameters.opening_count_array()[
			sanguis::creator::opening_type::entry
		] <= sanguis::creator::opening_count{1u}
	);

	FCPPT_ASSERT_ERROR(
		_parameters.opening_count_array()[
			sanguis::creator::opening_type::exit
		] <= sanguis::creator::opening_count{1u}
	);


	auto const rooms =
		fcppt::enum_::array<
			sanguis::creator::opening_type,
			::signed_rect
		>
		{{{
			entrance_room,
			exit_room
		}}};

	auto const opening_counts =
		_parameters.opening_count_array();

	auto const
	openings =
		fcppt::enum_::array_init<
			sanguis::creator::opening_container_array
		>
		(
			[
				&rooms,
				&opening_counts,
				&rect_center_pos
			](
				sanguis::creator::opening_type const _opening
			)
			{
				return
					opening_counts[_opening] >= sanguis::creator::opening_count{1u}
					?
						sanguis::creator::opening_container{
							sanguis::creator::opening{
								rect_center_pos(
									rooms[
										_opening
									]
								)
							}
						}
					:
						sanguis::creator::opening_container{}
					;

			}
		);

	FCPPT_LOG_DEBUG(
		_parameters.log(),
		fcppt::log::_
		 << openings[
				sanguis::creator::opening_type::entry
			].size()
		<< FCPPT_TEXT(" entries, ")
		<< openings[
				sanguis::creator::opening_type::exit
			].size()
		<< FCPPT_TEXT(" exits")
	);

	sanguis::creator::impl::set_opening_tiles(
		grid,
		openings
	);

	sanguis::creator::spawn_container
	spawners{};

	if(
		_parameters.spawn_boss().get()
	)
		spawners.push_back(
			sanguis::creator::impl::place_boss(
				openings)
		);

	sanguis::creator::impl::enemy_type_container const
	enemy_types{
		sanguis::creator::enemy_type::zombie00,
		sanguis::creator::enemy_type::zombie01,
		sanguis::creator::enemy_type::maggot
	};

	auto random_monster(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::random::wrapper::make_uniform_container_advanced<
				sanguis::creator::impl::random::uniform_int_wrapper
			>(
				enemy_types
			)
		)
	);

	{
		auto start = rects.begin();
		++start;
		for (auto room = start, end = rects.end(); room != end; ++room)
			spawners.push_back(
				sanguis::creator::spawn{
					sanguis::creator::spawn_pos{
						rect_center_pos(
							*room
						)
					},
					random_monster(
						_parameters.randgen()
					),
					sanguis::creator::spawn_type::single,
					sanguis::creator::enemy_kind::normal
				}
			);
	}

	return
		sanguis::creator::impl::result(
			grid,
			bg_grid,
			openings,
			spawners,
			sanguis::creator::destructible_container{}
		);
}
