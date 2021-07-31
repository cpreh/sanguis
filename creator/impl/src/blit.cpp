#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/creator/impl/blit.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/grid/pos_ref_range.hpp>
#include <fcppt/container/grid/pos_reference.hpp>
#include <fcppt/container/grid/range_dim.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/combine.hpp>
#include <boost/tuple/tuple.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Tile
>
sanguis::creator::enable_if_tile<
	Tile,
	void
>
sanguis::creator::impl::blit(
	fcppt::container::grid::pos_ref_range<
		sanguis::creator::tile_grid<
			Tile
		>
	> const _dest,
	fcppt::container::grid::pos_ref_range<
		sanguis::creator::tile_grid<
			Tile
		> const
	> const _source
)
{
	if(
		fcppt::container::grid::range_dim(
			_dest.min(),
			_dest.sup()
		)
		!=
		fcppt::container::grid::range_dim(
			_source.min(),
			_source.sup()
		)
	)
	{
		throw
			sanguis::creator::exception{
				FCPPT_TEXT("blit: dest and source have different sizes")
			};
	}

	for(
		boost::tuple<
			fcppt::container::grid::pos_reference<
				sanguis::creator::tile_grid<
					Tile
				>
			>,
			fcppt::container::grid::pos_reference<
				sanguis::creator::tile_grid<
					Tile
				> const
			>
		> const &element
		:
		boost::range::combine(
			_dest,
			_source
		)
	)
	{
		boost::get<
			0
		>(
			element
		).value() =
			boost::get<
				1
			>(
				element
			).value();
	}
}

#define SANGUIS_CREATOR_INSTANTIATE_BLIT(\
	tile_type\
)\
template \
sanguis::creator::enable_if_tile<\
	tile_type, \
	void \
> \
sanguis::creator::impl::blit( \
	fcppt::container::grid::pos_ref_range< \
		sanguis::creator::tile_grid< \
			tile_type \
		> \
	>, \
	fcppt::container::grid::pos_ref_range< \
		sanguis::creator::tile_grid< \
			tile_type \
		> const \
	> \
)

SANGUIS_CREATOR_INSTANTIATE_TILE(
	SANGUIS_CREATOR_INSTANTIATE_BLIT
);
