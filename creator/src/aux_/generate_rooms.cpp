#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/aux_/generate_rooms.hpp>
#include <sanguis/creator/aux_/random/generator.hpp>
#include <sanguis/creator/aux_/random/uniform_size.hpp>
#include <sanguis/creator/aux_/random/uniform_size_variate.hpp>
#include <sanguis/creator/aux_/rect.hpp>
#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <fcppt/math/box/contains_point.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/config/external_begin.hpp>
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

	struct
	line
	{
		sanguis::creator::rect::vector p1;
		sanguis::creator::rect::vector p2;
	};

	using pos =
		sanguis::creator::rect::vector;

	pos
	topleft(
		sanguis::creator::rect const &_rect
	)
	{
		return _rect.pos();
	}

	pos
	topright(
		sanguis::creator::rect const &_rect
	)
	{
		return pos{
			_rect.pos().x() + _rect.w(),
			_rect.pos().y()
		};
	}

	pos
	bottomleft(
		sanguis::creator::rect const &_rect
	)
	{
		return pos{
			_rect.pos().x(),
			_rect.pos().y() + _rect.h()
		};
	}

	pos
	bottomright(
		sanguis::creator::rect const &_rect
	)
	{
		return _rect.pos() + _rect.size();
	}

	::line
	side(
		sanguis::creator::rect const &_rect,
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
				throw sanguis::creator::exception(FCPPT_TEXT("there are only four sides to rectangle!"));
		}
	}

	bool
	intersect(
		::line const &line,
		sanguis::creator::rect const &rect
	)
	{
		return
			line.p2.x() >= rect.pos().x() &&
			line.p2.y() >= rect.pos().y() &&
			line.p1.x() <= rect.pos().x() + rect.w() &&
			line.p1.y() <= rect.pos().y() + rect.h();
	}

	edge
	clip(
		sanguis::creator::rect &cur,
		sanguis::creator::rect const &other
	)
	{
		using pos =
			sanguis::creator::rect::vector;
		using int_type =
			pos::value_type;

		pos const &p1 = cur.pos();
		pos const &o1 = other.pos();

		::edge last{
			::edge::none
		};

		if (
			fcppt::math::box::contains_point(cur, cur.pos()) &&
			fcppt::math::box::contains_point(cur, ::bottomright(other))
		)
		{
			cur.w(o1.x() - 1 - p1.x());
			last = ::edge::right;
		}

		if (
			intersect(::side(cur, ::edge::top), other)
		)
		{
			int_type oldy = p1.y();
			cur.pos(
				pos{
					::bottomright(other).x() + 1,
					p1.y()
				}
			);
			cur.h(cur.h() - p1.y() - oldy);
			last = ::edge::top;
		}

		if (
			intersect(::side(cur, ::edge::right), other)
		)
		{
			cur.w(o1.x() - 1 - p1.x());
			last = ::edge::right;
		}

		if (
			intersect(::side(cur, ::edge::bottom), other)
		)
		{
			cur.h(o1.y() - 1 - p1.y());
			last = ::edge::bottom;
		}

		if (
			intersect(::side(cur, ::edge::left), other)
		)
		{
			int_type oldx = p1.x();
			cur.pos(
				pos{
					o1.x() + other.w() + 1,
					p1.y()
				}
			);
			cur.w(cur.w() - p1.x() - oldx);
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
			unsigned
		>
	>
	uniform_int2;

	auto rand_int =
		[&_randgen]
		(
			 unsigned min,
			 unsigned max
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

	using int_type =
		sanguis::creator::size_type;

	int_type startw =
		rand_int(10u, 20u)();
	int_type starth =
		rand_int(10u, 20u)();

	std::vector<sanguis::creator::rect>
	rects{
		sanguis::creator::rect{
			sanguis::creator::rect::vector{
				rand_int(0u, _size.w() - startw)(),
				rand_int(0u, _size.h() - starth)()
			},
			sanguis::creator::rect::dim{
				startw,
				starth
			}
		}
	};

	for (
		unsigned i = 0u;
		i < 100u;
		++i
	)
	{
		fcppt::io::cout() << i << ' ';
		int_type w = rand_int(5u, 15u + i/2u)();
		int_type h = rand_int(5u, 15u + i/2u)();
		int_type x = rand_int(0u, _size.w() - w)();
		int_type y = rand_int(0u, _size.h() - h)();

		sanguis::creator::rect rect{
			sanguis::creator::rect::vector(
				x,
				y
			),
			sanguis::creator::rect::dim(
				w,
				h
			)
		};

		bool
		wellformed{
			true};

		::edge
		clipped_edge{
			::edge::none};
			

		fcppt::optional<
			sanguis::creator::rect
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

		// fcppt::io::cout() << (wellformed ? 1 : 0) << (neighbor ? 1 : 0) << ' ';

		// has become too small or doesn't touch any other rect
		if (!wellformed || !neighbor)
			continue;

		rects.push_back(
			rect
		);
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

	fcppt::io::cout() << FCPPT_TEXT("rects: ");
	for (
		auto &rect
		:
		rects
	)
	{
		fcppt::io::cout() << rect << std::endl;
		sanguis::creator::aux_::rect(
			rect,
			fill_with_wall
		);
	}

	return grid;

}
