#ifndef SANGUIS_TILES_SET_HPP_INCLUDED
#define SANGUIS_TILES_SET_HPP_INCLUDED

#include <sanguis/creator/is_tile.hpp>
#include <sanguis/tiles/orientation_map.hpp>
#include <sanguis/tiles/pair_fwd.hpp>
#include <sanguis/tiles/set_fwd.hpp>
#include <sanguis/tiles/symbol.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{

template<
	typename Tile
>
class set
{
	FCPPT_NONCOPYABLE(
		set
	);

	static_assert(
		sanguis::creator::is_tile<
			Tile
		>::value,
		"Tile must be a tile type"
	);
public:
	SANGUIS_TILES_SYMBOL
	set(
		sge::image2d::system &,
		sanguis::tiles::pair<
			Tile
		>
	);

	SANGUIS_TILES_SYMBOL
	set(
		set &&
	);

	SANGUIS_TILES_SYMBOL
	set &
	operator=(
		set &&
	);

	SANGUIS_TILES_SYMBOL
	~set();

	SANGUIS_TILES_SYMBOL
	sanguis::tiles::orientation_map const &
	orientations() const;

	SANGUIS_TILES_SYMBOL
	boost::filesystem::path const &
	path() const;
private:
	set(
		sge::image2d::system &,
		boost::filesystem::path const &
	);

	boost::filesystem::path path_;

	sanguis::tiles::orientation_map orientations_;
};

}
}

#endif
