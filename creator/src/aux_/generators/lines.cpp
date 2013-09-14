#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/signed_pos_fwd.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux_/bresenham.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/randgen.hpp>
#include <sanguis/creator/aux_/result.hpp>
#include <sanguis/creator/aux_/generators/lines.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

sanguis::creator::aux_::result
sanguis::creator::aux_::generators::lines(
	sanguis::creator::aux_::parameters const &_parameters
)
{
	sanguis::creator::grid ret(
		sanguis::creator::grid::dim(
			31u,
			31u
		),
		sanguis::creator::tile::nothing
	);

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::size_type
		>
	> uniform_int;

	uniform_int w_dist(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
			ret.size().w() - 1
		)
	);

	uniform_int h_dist(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
			ret.size().h() - 1
		)
	);


	auto draw_line = [&ret](
		int x0,
		int y0,
		int x1,
		int y1
	)
	{
		sanguis::creator::aux_::bresenham(
			sanguis::creator::signed_pos(
				x0,
				y0),
			sanguis::creator::signed_pos(
				x1,
				y1),
			[&ret](
				sanguis::creator::signed_pos pos
			)
			{
				auto p =
					fcppt::math::vector::structure_cast<
						sanguis::creator::pos
					>(
						pos);

				if (fcppt::container::grid::in_range(ret, p))
					ret[p] = sanguis::creator::tile::concrete_wall;
			}
		);
	};

	draw_line(5,5,5,10);
	draw_line(5,5,10,5);
	draw_line(5,5,5,0);
	draw_line(5,5,0,5);

	// FIXME
	sanguis::creator::opening_container openings
	{
		sanguis::creator::opening(
			sanguis::creator::pos(
				0,
				0)),
		sanguis::creator::opening(
			sanguis::creator::pos(
				0,
				1))
	};

	return
		sanguis::creator::aux_::result(
			ret,
			sanguis::creator::background_grid(
				ret.size(),
				sanguis::creator::background_tile::nothing
			),
			openings,
			sanguis::creator::spawn_container()
		);
}

