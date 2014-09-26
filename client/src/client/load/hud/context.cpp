#include <sanguis/weapon_type.hpp>
#include <sanguis/client/load/hud/context.hpp>
#include <sanguis/client/load/hud/make_weapon_icons.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_opt.hpp>


sanguis::client::load::hud::context::context(
	sanguis::client::load::resource::textures const &_textures
)
:
	weapon_icons_(
		sanguis::client::load::hud::make_weapon_icons(
			_textures
		)
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
	fcppt::optional<
		weapon_icon_map::mapped_type
	> const icon{
		fcppt::container::find_opt(
			weapon_icons_,
			_weapon_type
		)
	};

	FCPPT_ASSERT_ERROR(
		icon
	);

	return
		icon->get();
}
