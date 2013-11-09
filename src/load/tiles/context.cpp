#include <sanguis/creator/tile.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/tiles/background_to_name.hpp>
#include <sanguis/load/tiles/category.hpp>
#include <sanguis/load/tiles/context.hpp>
#include <sanguis/load/tiles/name.hpp>
#include <sanguis/load/tiles/set.hpp>
#include <sanguis/load/tiles/to_name.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>


sanguis::load::tiles::context::context(
	sanguis::load::resource::textures const &_textures
)
:
	textures_(
		_textures
	),
	sets_(),
	background_sets_()/*,
	fog_of_war_(
		_textures,
		sanguis::load::tiles::category(
			FCPPT_TEXT("misc")
		),
		sanguis::load::tiles::name(
			FCPPT_TEXT("fog_of_war")
		)
	)*/
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
	return
		this->any_set(
			sets_,
			_tile,
			&sanguis::load::tiles::to_name,
			sanguis::load::tiles::category(
				FCPPT_TEXT("foreground")
			)
		);
}

sanguis::load::tiles::set const &
sanguis::load::tiles::context::set(
	sanguis::creator::background_tile const _tile
)
{
	return
		this->any_set(
			background_sets_,
			_tile,
			&sanguis::load::tiles::background_to_name,
			sanguis::load::tiles::category(
				FCPPT_TEXT("background")
			)
		);
}

/*
sanguis::load::tiles::set const &
sanguis::load::tiles::context::fog_of_war()
{
	return
		fog_of_war_;
}*/

template<
	typename Map,
	typename ToName
>
sanguis::load::tiles::set const &
sanguis::load::tiles::context::any_set(
	Map &_map,
	typename Map::key_type const _tile,
	ToName const _to_name,
	sanguis::load::tiles::category const &_category
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
				sanguis::load::tiles::set
			>(
				textures_,
				_category,
				sanguis::load::tiles::name(
					_to_name(
						_tile
					)
				)
			)
		).first->second;
}
