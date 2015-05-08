#ifndef SANGUIS_TILES_PAIR_HPP_INCLUDED
#define SANGUIS_TILES_PAIR_HPP_INCLUDED

#include <sanguis/tiles/is_tile.hpp>
#include <sanguis/tiles/pair_fwd.hpp>
#include <sanguis/tiles/symbol.hpp>
#include <fcppt/homogenous_pair_impl.hpp>


namespace sanguis
{
namespace tiles
{

template<
	typename Tile
>
class pair
{
public:
	static_assert(
		sanguis::tiles::is_tile<
			Tile
		>::value,
		"Tile must be a tile type"
	);

	SANGUIS_TILES_SYMBOL
	pair(
		Tile,
		Tile
	);

	Tile
	first() const;

	Tile
	second() const;
private:
	typedef
	fcppt::homogenous_pair<
		Tile
	>
	impl_type;

	impl_type const impl_;
};

}
}

#endif
