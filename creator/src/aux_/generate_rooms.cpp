#include <sanguis/creator/aux_/generate_rooms.hpp>
#include <sanguis/creator/aux_/random/generator.hpp>
#include <sanguis/creator/aux_/random/uniform_size.hpp>
#include <sanguis/creator/aux_/random/uniform_size_variate.hpp>
#include <sanguis/creator/aux_/rect.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <fcppt/math/box/contains_point.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{
	enum class
	edge
	{
		none,
		right,
		top,
		left,
		bottom
	};

	using signed_rect =
		fcppt::math::box::object<
			sanguis::creator::difference_type,
			2
		>;

	using pos_type =
		sanguis::creator::signed_pos;

	using int_type =
		pos_type::value_type;

	struct
	line
	{
		pos_type p1;
		pos_type p2;
	};

	pos_type
	topleft(
		::signed_rect const &_rect
	)
	{
		return
			_rect.pos();
	}

	pos_type
	topright(
		::signed_rect const &_rect
	)
	{
		return pos_type{
			_rect.right(),
			_rect.top()
		};
	}

	pos_type
	bottomleft(
		::signed_rect const &_rect
	)
	{
		return pos_type{
			_rect.left(),
			_rect.bottom()
		};
	}

	pos_type
	bottomright(
		::signed_rect const &_rect
	)
	{
		return
			_rect.pos() + _rect.size();
	}

	::line
	side(
		::signed_rect const &_rect,
		::edge _edge
	){

		switch(_edge)
		{
			case ::edge::top:
				return ::line{topleft(_rect), topright(_rect)};
			case ::edge::left:
				return ::line{topleft(_rect), bottomleft(_rect)};
			case ::edge::bottom:
				return ::line{bottomleft(_rect), bottomright(_rect)};
			case ::edge::right:
				return ::line{topright(_rect), bottomright(_rect)};
			default:
				throw sanguis::creator::exception(
					FCPPT_TEXT("there are only four sides to a rectangle!"));
		}
	}

	bool
	intersect(
		::line const &_line,
		::signed_rect const &_rect
	)
	{
		return
			_line.p2.x() >= _rect.left() &&
			_line.p2.y() >= _rect.top() &&
			_line.p1.x() <= _rect.left() + _rect.w() &&
			_line.p1.y() <= _rect.top() + _rect.h();
	}

	edge
	clip(
		::signed_rect &cur,
		::signed_rect const &other
	)
	{

		::edge last{
			::edge::none
		};

		if (
			fcppt::math::box::contains_point(cur, cur.pos()) &&
			fcppt::math::box::contains_point(cur, ::bottomright(other))
		)
		{
			cur.w(other.left() - cur.left() - 1);
			last = ::edge::right;
		}

		if (
			intersect(::side(cur, ::edge::top), other)
		)
		{
			::int_type oldy = cur.top();
			cur.top(other.bottom() + 1);
			cur.h(cur.h() - (cur.top() - oldy));
			last = ::edge::top;
		}

		if (
			intersect(::side(cur, ::edge::right), other)
		)
		{
			cur.w(other.left() - cur.left() - 1);
			last = ::edge::right;
		}

		if (
			intersect(::side(cur, ::edge::bottom), other)
		)
		{
			cur.h(other.top() - cur.top() - 1);
			last = ::edge::bottom;
		}

		if (
			intersect(::side(cur, ::edge::left), other)
		)
		{
			::int_type oldx = cur.left();
			cur.left(
				other.right() + 1);
			cur.w(cur.w() - (cur.left() - oldx));
			last = ::edge::left;
		}

		return last;
	}
}

sanguis::creator::grid
sanguis::creator::aux_::generate_rooms(
	sanguis::creator::dim _size,
	sanguis::creator::tile _wall_tile,
	sanguis::creator::tile _floor_tile,
	sanguis::creator::aux_::random::generator &_randgen
)
{
	typedef
	fcppt::random::distribution::basic<
		sanguis::creator::aux_::random::uniform_int<
			::int_type
		>
	>
	uniform_int2;

	auto rand_int =
		[&_randgen]
		(
			 ::int_type min,
			 ::int_type max
		 )
		{
			return
			fcppt::random::make_variate(
				_randgen,
				uniform_int2{
					uniform_int2::param_type::min{
						min
					},
					uniform_int2::param_type::max{
						max
					}
				}
			);
		};

	::int_type startw =
		rand_int(10, 20)();
	::int_type starth =
		rand_int(10, 20)();

	std::vector<
		signed_rect
	>
	rects{
		signed_rect{
			signed_rect::vector{
				rand_int(0, static_cast<::int_type>(_size.w()) - startw - 1)(),
				rand_int(0, static_cast<::int_type>(_size.h()) - starth - 1)()
			},
			signed_rect::dim{
				startw,
				starth
			}
		}
	};

	for (
		::int_type i = 0;
		i < 100;
		++i
	)
	{
		::int_type w = rand_int(5, std::min(15 + i/2, static_cast<::int_type>(_size.w() - 1)))();
		::int_type h = rand_int(5, std::min(15 + i/2, static_cast<::int_type>(_size.h() - 1)))();
		::int_type x = rand_int(0, static_cast<::int_type>(_size.w()) - w - 1)();
		::int_type y = rand_int(0, static_cast<::int_type>(_size.h()) - h - 1)();

		signed_rect rect{
			signed_rect::vector{
				x,
				y
			},
			signed_rect::dim{
				w,
				h
			}
		};

		bool
		wellformed{
			true};

		::edge
		clipped_edge{
			::edge::none};
			

		fcppt::optional<
			signed_rect
		> neighbor;

		for (
			auto const &other
			:
			rects
		)
		{
			clipped_edge =
				::clip(
					rect,
					other);

			// rect has just been clipped with other,
			// so it's next to it
			if (clipped_edge != ::edge::none)
				neighbor = other;

			wellformed =
				rect.w() > 2
				&&
				rect.h() > 2;

			// rect has been clipped into oblivion, discard it
			if (!wellformed)
				break;
		}

		// has become too small or doesn't touch any other rect
		if (!wellformed || !neighbor)
			continue;

		rects.push_back(
				rect);
	}

	sanguis::creator::grid
	grid{
		sanguis::creator::grid::dim{
			_size
		},
		sanguis::creator::tile::nothing
	};

	auto fill_with_wall(
		[
			&grid,
			&_wall_tile
		]
		(sanguis::creator::pos _pos)
		{
			grid[
				_pos
			]
			=
			_wall_tile;
		}
	);

	for (
		auto &rect
		:
		rects
	)
	{
		sanguis::creator::aux_::rect(
			fcppt::math::box::structure_cast<
				sanguis::creator::rect
			>(
				rect
			),
			fill_with_wall
		);
	}

	return grid;

}
