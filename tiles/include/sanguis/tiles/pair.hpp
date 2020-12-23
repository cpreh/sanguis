#ifndef SANGUIS_TILES_PAIR_HPP_INCLUDED
#define SANGUIS_TILES_PAIR_HPP_INCLUDED

#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/creator/is_tile.hpp>
#include <sanguis/tiles/pair_fwd.hpp>
#include <sanguis/tiles/symbol.hpp>
#include <fcppt/tuple/object_impl.hpp>


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
		sanguis::creator::is_tile<
			Tile
		>::value,
		"Tile must be a tile type"
	);

	SANGUIS_TILES_SYMBOL
	pair(
		Tile,
		Tile
	);

	[[nodiscard]]
	Tile
	first() const;

	[[nodiscard]]
	Tile
	second() const;
private:
	using
	impl_type
	=
	fcppt::tuple::object<
		Tile,
		Tile
	>;

	impl_type impl_;
};

}
}

#define SANGUIS_TILES_DECLARE_TILE(\
	tile_type\
)\
extern \
template \
class \
sanguis::tiles::pair<\
	tile_type \
>

SANGUIS_CREATOR_INSTANTIATE_TILE(
	SANGUIS_TILES_DECLARE_TILE
);

#endif
