#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/entities/hover/name_and_health_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/weapon_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/hover/create.hpp>
#include <sanguis/client/draw2d/scene/hover/name_and_health.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/variant/match.hpp>


sanguis::client::draw2d::scene::hover::base_unique_ptr
sanguis::client::draw2d::scene::hover::create(
	sanguis::client::draw2d::scene::hover::parameters const &_parameters,
	sanguis::client::draw2d::entities::hover::info const &_info
)
{
	return
		fcppt::variant::match(
			_info.get(),
			[
				&_parameters
			](
				sanguis::client::draw2d::entities::hover::name_and_health const &_name_and_health
			)
			{
				return
					sanguis::client::draw2d::scene::hover::base_unique_ptr{
						fcppt::make_unique_ptr<
							sanguis::client::draw2d::scene::hover::name_and_health
						>(
							_parameters.renderer(),
							_parameters.font(),
							_parameters.center(),
							_parameters.radius(),
							_name_and_health
						)
					};
			},
			[
				&_parameters
			](
				sanguis::client::draw2d::entities::hover::weapon const &_weapon
			)
			{
				return
					sanguis::client::draw2d::scene::hover::base_unique_ptr{
						fcppt::make_unique_ptr<
							sanguis::client::draw2d::scene::hover::weapon
						>(
							_parameters.gui_style(),
							_parameters.gui_renderer(),
							_parameters.renderer(),
							_parameters.font(),
							_parameters.center(),
							_parameters.load_context(),
							_parameters.player_weapons(),
							_weapon
						)
					};
			}
		);
}
