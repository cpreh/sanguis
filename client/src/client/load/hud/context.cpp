#include <sanguis/weapon_type.hpp>
#include <sanguis/client/load/hud/context.hpp>
#include <sanguis/client/load/hud/make_weapon_icons.hpp>
#include <sanguis/client/load/hud/weapon_icon_map.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/from.hpp>


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
		fcppt::optional::from(
			fcppt::optional::copy_value(
				fcppt::container::find_opt_mapped(
					weapon_icons_,
					_weapon_type
				)
			),
			[
				this
			]()
			{
				return
					fcppt::make_cref(
						missing_texture_
					);
			}
		).get();
}
