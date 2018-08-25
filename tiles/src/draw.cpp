#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/min.hpp>
#include <sanguis/creator/sup.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/collection_fwd.hpp>
#include <sanguis/tiles/draw.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/log.hpp>
#include <sanguis/tiles/impl/draw_connecting.hpp>
#include <sanguis/tiles/impl/draw_non_connecting.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/container/grid/clamped_sup.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/dim.hpp>


sanguis::tiles::cell_container
sanguis::tiles::draw(
	sanguis::tiles::log const &_log,
	sanguis::creator::grid const &_foreground,
	sanguis::creator::background_grid const &_background,
	sanguis::tiles::collection &_collection,
	sanguis::creator::min const _min,
	sanguis::creator::sup const _sup
)
{
	FCPPT_ASSERT_PRE(
		_foreground.size()
		==
		_background.size()
	);

	sanguis::creator::grid::dim const min_size{
		fcppt::math::dim::fill<
			sanguis::creator::grid::dim
		>(
			1u
		)
	};

	if(
		_foreground.size()
		<=
		min_size
	)
		return
			sanguis::tiles::cell_container();

	sanguis::creator::min const lower_bound(
		_min
	);

	sanguis::creator::min const connecting_lower_bound(
		_min.get()
		+
		min_size
	);

	sanguis::creator::sup const upper_bound(
		fcppt::container::grid::clamped_sup(
			_sup.get(),
			_foreground.size()
		)
	);

	return
		fcppt::container::join(
			sanguis::tiles::impl::draw_connecting(
				_log.main_log(),
				_collection,
				sanguis::tiles::error::missing_background,
				_background,
				connecting_lower_bound,
				upper_bound
			),
			sanguis::tiles::impl::draw_connecting(
				_log.main_log(),
				_collection,
				sanguis::tiles::error::missing_foreground,
				_foreground,
				connecting_lower_bound,
				upper_bound
			),
			sanguis::tiles::impl::draw_non_connecting(
				_log.main_log(),
				_collection,
				sanguis::tiles::error::missing_object,
				_foreground,
				lower_bound,
				upper_bound
			)
		);
}
