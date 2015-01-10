#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/light.hpp>
#include <sanguis/client/draw2d/scene/light_texture_coordinates.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/client/category.hpp>
#include <sanguis/client/draw2d/sprite/client/object.hpp>
#include <sanguis/client/draw2d/sprite/client/parameters.hpp>
#include <sanguis/client/draw2d/sprite/client/system_decl.hpp>
#include <sanguis/client/load/context.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/scoped_single.hpp>
#include <sge/renderer/state/core/sampler/address/mode.hpp>
#include <sge/renderer/state/core/sampler/address/mode_all.hpp>
#include <sge/renderer/state/core/sampler/filter/point.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/sprite/center.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::light::light(
	sanguis::client::load::context const &_load_context,
	sanguis::client::draw2d::sprite::client::system &_client_system,
	sge::viewport::manager &_viewport_manager
)
:
	client_system_(
		_client_system
	),
	texture_(
		_load_context.resources().textures().load(
			sanguis::client::load::resource::texture_identifier(
				FCPPT_TEXT("light")
			)
		)
	),
	sprite_(
		sanguis::client::draw2d::sprite::client::parameters()
		.connection(
			client_system_.connection(
				sanguis::client::draw2d::sprite::client::category::light
			)
		)
		.pos(
			sanguis::client::draw2d::sprite::point::null()
		)
		.size(
			fcppt::math::dim::structure_cast<
				sanguis::client::draw2d::sprite::dim,
				fcppt::cast::size_fun
			>(
				fcppt::math::dim::to_signed(
					sanguis::client::draw2d::scene::background_dim(
						client_system_.renderer()
					)
				)
			)
		)
		.texture(
			sanguis::client::draw2d::sprite::client::object::texture_type{
				texture_
			}
		)
		.texture_coordinates(
			sanguis::client::draw2d::scene::light_texture_coordinates(
				client_system_.renderer(),
				texture_
			)
		)
	),
	sampler_state_{
		_client_system.renderer().create_sampler_state(
			sge::renderer::state::core::sampler::parameters{
				sge::renderer::state::core::sampler::address::mode_all(
					sge::renderer::state::core::sampler::address::mode::clamp
				),
				sge::renderer::state::core::sampler::filter::point()
			}
		)
	},
	viewport_connection_(
		_viewport_manager.manage_callback(
			std::bind(
				&sanguis::client::draw2d::scene::light::reset_viewport,
				this
			)
		)
	)
{
}

sanguis::client::draw2d::scene::light::~light()
{
}

void
sanguis::client::draw2d::scene::light::draw(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::player_center const _player_center
)
{
	sge::sprite::center(
		sprite_,
		_player_center.get().get()
	);

	sge::renderer::state::core::sampler::scoped_single const sampler_state{
		_render_context,
		sge::renderer::texture::stage{
			0u
		},
		*sampler_state_
	};

	client_system_.render(
		_render_context,
		sanguis::client::draw2d::sprite::client::category::light
	);
}

void
sanguis::client::draw2d::scene::light::reset_viewport()
{
	sprite_.texture_coordinates(
		sanguis::client::draw2d::scene::light_texture_coordinates(
			client_system_.renderer(),
			texture_
		)
	);

	sprite_.size(
		fcppt::math::dim::structure_cast<
			sanguis::client::draw2d::sprite::dim,
			fcppt::cast::size_fun
		>(
			fcppt::math::dim::to_signed(
				sanguis::client::draw2d::scene::background_dim(
					client_system_.renderer()
				)
			)
		)
	);
}
