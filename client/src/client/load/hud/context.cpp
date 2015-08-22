#include <sanguis/weapon_type.hpp>
#include <sanguis/client/load/hud/context.hpp>
#include <sanguis/client/load/hud/make_weapon_icons.hpp>
#include <sanguis/client/load/hud/weapon_icon_map.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/container/find_opt_mapped.hpp>


sanguis::client::load::hud::context::context(
	sanguis::client::load::resource::textures const &_textures
)
:
	weapon_icons_(
		sanguis::client::load::hud::make_weapon_icons(
			_textures
		)
	),
	missing_texture_(
		_textures.missing_texture()
	)
{
}

sanguis::client::load::hud::context::~context()
{
}

sge::texture::part const &
sanguis::client::load::hud::context::weapon_icon(
	sanguis::weapon_type const _weapon_type
)
{
	return
		fcppt::maybe(
			fcppt::container::find_opt_mapped(
				weapon_icons_,
				_weapon_type
			),
			[
				this
			]()
			-> sge::texture::part const &
			{
				return
					missing_texture_;
			},
			[](
				sanguis::client::load::hud::weapon_icon_map::mapped_type const &_ref
			)
			-> sge::texture::part const &
			{
				return
					_ref.get();
			}
		);
}
