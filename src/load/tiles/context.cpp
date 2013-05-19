#include <sanguis/creator/tile.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/tiles/context.hpp>
#include <sanguis/load/tiles/set.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>


sanguis::load::tiles::context::context(
	sanguis::load::resource::textures const &_textures
)
:
	textures_(
		_textures
	),
	sets_()
{
}

sanguis::load::tiles::context::~context()
{
}

sanguis::load::tiles::set const &
sanguis::load::tiles::context::set(
	sanguis::creator::tile const _tile
)
{
	set_map::const_iterator const it(
		sets_.find(
			_tile
		)
	);

	if(
		it != sets_.end()
	)
		return *it->second;

	return
		*fcppt::container::ptr::insert_unique_ptr_map(
			sets_,
			_tile,
			fcppt::make_unique_ptr<
				sanguis::load::tiles::set
			>(
				textures_,
				_tile
			)
		).first->second;
}
