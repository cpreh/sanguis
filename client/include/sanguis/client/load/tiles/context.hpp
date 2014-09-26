#ifndef SANGUIS_CLIENT_LOAD_TILES_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_CONTEXT_HPP_INCLUDED

#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/tiles/background_tile_pair_fwd.hpp>
#include <sanguis/client/load/tiles/category.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/client/load/tiles/pair.hpp>
#include <sanguis/client/load/tiles/set_fwd.hpp>
#include <sanguis/client/load/tiles/tile_pair_fwd.hpp>
#include <sanguis/creator/background_tile_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/homogenous_pair_comparison.hpp>
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
		sanguis::client::load::tiles::tile_pair
	);

	sanguis::client::load::tiles::set const &
	set(
		sanguis::client::load::tiles::background_tile_pair
	);

	sge::texture::part const &
	missing_texture() const;

	sge::texture::part const &
	missing_background_texture() const;

	sge::texture::part const &
	missing_object_texture() const;
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

	template<
		typename TileType
	>
	// TODO: unordered_map
	using
	map_type
	=
	std::map<
		sanguis::client::load::tiles::pair<
			TileType
		>,
		sanguis::client::load::tiles::set
	>;

	typedef
	map_type<
		sanguis::creator::tile
	>
	set_map;

	typedef
	map_type<
		sanguis::creator::background_tile
	>
	background_set_map;

	sanguis::client::load::resource::textures const &textures_;

	set_map sets_;

	background_set_map background_sets_;

	sge::texture::const_part_unique_ptr const missing_texture_;

	sge::texture::const_part_unique_ptr const missing_background_texture_;

	sge::texture::const_part_unique_ptr const missing_object_texture_;
};

}
}
}
}

#endif
