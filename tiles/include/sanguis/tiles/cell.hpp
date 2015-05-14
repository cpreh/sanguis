#ifndef SANGUIS_TILES_CELL_HPP_INCLUDED
#define SANGUIS_TILES_CELL_HPP_INCLUDED

#include <sanguis/tiles/cell_fwd.hpp>
#include <sanguis/tiles/content.hpp>
#include <sanguis/tiles/pos.hpp>
#include <sanguis/tiles/symbol.hpp>


namespace sanguis
{
namespace tiles
{

class cell
{
public:
	cell(
		sanguis::tiles::pos,
		sanguis::tiles::content const &
	);

	SANGUIS_TILES_SYMBOL
	sanguis::tiles::pos const
	pos() const;

	SANGUIS_TILES_SYMBOL
	sanguis::tiles::content const &
	content() const;
private:
	sanguis::tiles::pos pos_;

	sanguis::tiles::content content_;
};

}
}

#endif
