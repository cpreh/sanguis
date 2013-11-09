#ifndef SANGUIS_LOAD_TILES_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_TILES_CONTEXT_HPP_INCLUDED

#include <sanguis/creator/background_tile_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/tiles/category.hpp>
#include <sanguis/load/tiles/context_fwd.hpp>
#include <sanguis/load/tiles/set.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
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
		sanguis::load::resource::textures const &
	);

	~context();

	sanguis::load::tiles::set const &
	set(
		sanguis::creator::tile
	);

	sanguis::load::tiles::set const &
	set(
		sanguis::creator::background_tile
	);

	sanguis::load::tiles::set const &
	fog_of_war();
private:
	template<
		typename Map,
		typename ToName
	>
	sanguis::load::tiles::set const &
	any_set(
		Map &,
		typename Map::key_type,
		ToName,
		sanguis::load::tiles::category const &
	);

	typedef
	boost::ptr_map<
		sanguis::creator::tile,
		sanguis::load::tiles::set
	>
	set_map;

	typedef
	boost::ptr_map<
		sanguis::creator::background_tile,
		sanguis::load::tiles::set
	>
	background_set_map;

	sanguis::load::resource::textures const &textures_;

	set_map sets_;

	background_set_map background_sets_;

	sanguis::load::tiles::set fog_of_war_;
};

}
}
}

#endif
