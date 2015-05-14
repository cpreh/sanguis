#ifndef SANGUIS_TILES_IMPL_DRAW_BASE_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_DRAW_BASE_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/tiles/cell.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/lower_bound.hpp>
#include <sanguis/tiles/pos.hpp>
#include <sanguis/tiles/upper_bound.hpp>
#include <sanguis/tiles/impl/optional_content.hpp>
#include <sanguis/tiles/impl/shift.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/grid/make_pos_crange_start_end.hpp>
#include <fcppt/container/grid/pos_reference_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_signed.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

template<
	typename Tile
>
sanguis::tiles::cell_container
draw_base(
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::tiles::lower_bound const _lower_bound,
	sanguis::tiles::upper_bound const _upper_bound,
	sanguis::tiles::impl::shift const _shift,
	std::function<
		sanguis::tiles::impl::optional_content (
			sanguis::creator::pos
		)
	> const _get_content
)
{
	sanguis::tiles::pos const tile_dim(
		fcppt::math::vector::fill<
			sanguis::tiles::pos
		>(
			fcppt::cast::size<
				sanguis::tiles::unit
			>(
				fcppt::cast::to_signed(
					sanguis::creator::tile_size::value
				)
			)
		)
	);

	return
		fcppt::algorithm::map_optional<
			sanguis::tiles::cell_container
		>(
			fcppt::container::grid::make_pos_crange_start_end(
				_grid,
				_lower_bound.get(),
				_upper_bound.get()
			),
			[
				tile_dim,
				&_get_content,
				_shift
			](
				fcppt::container::grid::pos_reference<
					sanguis::creator::tile_grid<
						Tile
					> const
				> const _element
			)
			{
				return
					fcppt::optional_bind_construct(
						_get_content(
							_element.pos()
						),
						[
							tile_dim,
							&_element,
							_shift
						](
							sanguis::tiles::content const &_content
						)
						{
							return
								sanguis::tiles::cell(
									fcppt::math::vector::structure_cast<
										sanguis::tiles::pos,
										fcppt::cast::size_fun
									>(
										fcppt::math::vector::to_signed(
											_element.pos()
										)
									)
									*
									tile_dim
									+
									_shift.get()
									,
									_content
								);
						}
					);
			}
		);
}

}
}
}

#endif
