#ifndef SANGUIS_CLIENT_LOAD_TILES_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_CONTEXT_HPP_INCLUDED

#include <sanguis/creator/background_tile_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/tiles/category.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/client/load/tiles/set_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace tiles
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit
	context(
		sanguis::client::load::resource::textures const &
	);

	~context();

	sanguis::client::load::tiles::set const &
	set(
		sanguis::creator::tile
	);

	sanguis::client::load::tiles::set const &
	set(
		sanguis::creator::background_tile
	);
private:
	template<
		typename Map,
		typename ToName
	>
	sanguis::client::load::tiles::set const &
	any_set(
		Map &,
		typename Map::key_type,
		ToName,
		sanguis::client::load::tiles::category const &
	);

	typedef
	std::map<
		sanguis::creator::tile,
		sanguis::client::load::tiles::set
	>
	set_map;

	typedef
	std::map<
		sanguis::creator::background_tile,
		sanguis::client::load::tiles::set
	>
	background_set_map;

	sanguis::client::load::resource::textures const &textures_;

	set_map sets_;

	background_set_map background_sets_;
};

}
}
}
}

#endif
