#include <sanguis/creator/tile.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/tiles/background_to_name.hpp>
#include <sanguis/client/load/tiles/category.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/client/load/tiles/name.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sanguis/client/load/tiles/to_name.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>


sanguis::client::load::tiles::context::context(
	sanguis::client::load::resource::textures const &_textures
)
:
	textures_(
		_textures
	),
	sets_(),
	background_sets_()
{
}

sanguis::client::load::tiles::context::~context()
{
}

sanguis::client::load::tiles::set const &
sanguis::client::load::tiles::context::set(
	sanguis::creator::tile const _tile
)
{
	return
		this->any_set(
			sets_,
			_tile,
			&sanguis::client::load::tiles::to_name,
			sanguis::client::load::tiles::category(
				FCPPT_TEXT("foreground")
			)
		);
}

sanguis::client::load::tiles::set const &
sanguis::client::load::tiles::context::set(
	sanguis::creator::background_tile const _tile
)
{
	return
		this->any_set(
			background_sets_,
			_tile,
			&sanguis::client::load::tiles::background_to_name,
			sanguis::client::load::tiles::category(
				FCPPT_TEXT("background")
			)
		);
}

template<
	typename Map,
	typename ToName
>
sanguis::client::load::tiles::set const &
sanguis::client::load::tiles::context::any_set(
	Map &_map,
	typename Map::key_type const _tile,
	ToName const _to_name,
	sanguis::client::load::tiles::category const &_category
)
{
	typename Map::const_iterator const it(
		_map.find(
			_tile
		)
	);

	if(
		it != _map.end()
	)
		return *it->second;

	return
		*fcppt::container::ptr::insert_unique_ptr_map(
			_map,
			_tile,
			fcppt::make_unique_ptr<
				sanguis::client::load::tiles::set
			>(
				textures_,
				_category,
				sanguis::client::load::tiles::name(
					_to_name(
						_tile
					)
				)
			)
		).first->second;
}
