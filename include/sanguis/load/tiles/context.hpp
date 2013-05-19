#ifndef SANGUIS_LOAD_TILES_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_TILES_CONTEXT_HPP_INCLUDED

#include <sanguis/creator/tile_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/tiles/context_fwd.hpp>
#include <sanguis/load/tiles/set_fwd.hpp>
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
private:
	typedef
	boost::ptr_map<
		sanguis::creator::tile,
		sanguis::load::tiles::set
	>
	set_map;

	sanguis::load::resource::textures const &textures_;

	set_map sets_;
};

}
}
}

#endif
