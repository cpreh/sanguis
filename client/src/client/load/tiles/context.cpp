#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/tiles/background_tile_pair.hpp>
#include <sanguis/client/load/tiles/background_to_name.hpp>
#include <sanguis/client/load/tiles/category.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/client/load/tiles/name.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sanguis/client/load/tiles/sort_pair.hpp>
#include <sanguis/client/load/tiles/tile_pair.hpp>
#include <sanguis/client/load/tiles/to_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/get_or_insert.hpp>


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
	sanguis::client::load::tiles::tile_pair const _pair
)
{
	return
		this->any_set(
			sets_,
			_pair,
			&sanguis::client::load::tiles::to_name,
			sanguis::client::load::tiles::category(
				FCPPT_TEXT("foreground")
			)
		);
}

sanguis::client::load::tiles::set const &
sanguis::client::load::tiles::context::set(
	sanguis::client::load::tiles::background_tile_pair const _pair
)
{
	return
		this->any_set(
			background_sets_,
			_pair,
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
	typename Map::key_type const _pair,
	ToName const _to_name,
	sanguis::client::load::tiles::category const &_category
)
{
	return
		fcppt::container::get_or_insert(
			_map,
			sanguis::client::load::tiles::sort_pair(
				_pair
			),
			[
				this,
				&_to_name,
				&_category
			](
				typename Map::key_type const _sorted
			)
			{
				return
					sanguis::client::load::tiles::set(
						textures_,
						_category,
						sanguis::client::load::tiles::name(
							_to_name(
								_sorted.first
							)
							+
							FCPPT_TEXT('_')
							+
							_to_name(
								_sorted.second
							)
						)
					);
			}
		);
}
