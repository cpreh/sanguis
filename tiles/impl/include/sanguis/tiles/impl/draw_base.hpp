#ifndef SANGUIS_TILES_IMPL_DRAW_BASE_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_DRAW_BASE_HPP_INCLUDED

#include <sanguis/creator/min.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/sup.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/tiles/cell.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/pos.hpp>
#include <sanguis/tiles/impl/content_path.hpp>
#include <sanguis/tiles/impl/get_content_function.hpp>
#include <sanguis/tiles/impl/is_background.hpp>
#include <sanguis/tiles/impl/shift.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/grid/make_pos_ref_crange_start_end.hpp>
#include <fcppt/container/grid/pos_reference_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_signed.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


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
	sanguis::creator::min const _min,
	sanguis::creator::sup const _sup,
	sanguis::tiles::impl::shift const &_shift,
	sanguis::tiles::impl::get_content_function const &_get_content
)
{
	auto const tile_dim(
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
			fcppt::container::grid::make_pos_ref_crange_start_end(
				_grid,
				_min,
				_sup
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
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
				return
					fcppt::optional::map(
						_get_content(
							_element.pos()
						),
						[
							tile_dim,
							&_element,
							_shift
						](
							sanguis::tiles::impl::content_path const &_content_path
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
									_content_path.content()
									,
									_content_path.path()
									,
									sanguis::tiles::impl::is_background<
										Tile
									>()
								);
						}
					);
FCPPT_PP_POP_WARNING
			}
		);
}

}
}
}

#endif
