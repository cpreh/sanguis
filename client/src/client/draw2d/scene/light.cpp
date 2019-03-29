#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/light.hpp>
#include <sanguis/client/draw2d/scene/light_texture_coordinates.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/client/category.hpp>
#include <sanguis/client/draw2d/sprite/client/object.hpp>
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
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/roles/texture_coordinates0.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

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
		sge::sprite::roles::connection{} =
			client_system_.connection(
				sanguis::client::draw2d::sprite::client::category::light
			),
		sge::sprite::roles::pos{} =
			fcppt::math::vector::null<
				sanguis::client::draw2d::sprite::point
			>(),
		sge::sprite::roles::size{} =
			fcppt::math::dim::structure_cast<
				sanguis::client::draw2d::sprite::dim,
				fcppt::cast::size_fun
			>(
				fcppt::math::dim::to_signed(
					sanguis::client::draw2d::scene::background_dim(
						client_system_.renderer()
					)
				)
			),
		sge::sprite::roles::texture0{} =
			sanguis::client::draw2d::sprite::client::object::texture_type{
				texture_
			},
		sge::sprite::roles::texture_coordinates0{} =
			sanguis::client::draw2d::scene::light_texture_coordinates(
				client_system_.renderer(),
				texture_
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
			sge::viewport::manage_callback{
				std::bind(
					&sanguis::client::draw2d::scene::light::reset_viewport,
					this
				)
			}
		)
	)
{
}

FCPPT_PP_POP_WARNING

sanguis::client::draw2d::scene::light::~light()
{
}

void
sanguis::client::draw2d::scene::light::draw(
	sge::renderer::context::core &_render_context
)
{
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
