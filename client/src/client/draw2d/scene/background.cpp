#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/scene/background.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/background_texture_coordinates.hpp>
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
#include <sge/renderer/target/viewport.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/roles/texture_coordinates0.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::background::background(
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
				FCPPT_TEXT("background")
			)
		)
	),
	sprite_(
		sge::sprite::roles::connection{} =
			client_system_.connection(
				sanguis::client::draw2d::sprite::client::category::background
			),
		sge::sprite::roles::pos{} =
			sanguis::client::draw2d::sprite::point::null(),
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
			sanguis::client::draw2d::scene::background_texture_coordinates(
				sanguis::client::draw2d::translation(
					sanguis::client::draw2d::translation::value_type::null()
				),
				client_system_.renderer(),
				texture_
			)
	),
	viewport_connection_(
		_viewport_manager.manage_callback(
			std::bind(
				&sanguis::client::draw2d::scene::background::reset_viewport,
				this
			)
		)
	)
{
}

sanguis::client::draw2d::scene::background::~background()
{
}

void
sanguis::client::draw2d::scene::background::render(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::translation const _translation
)
{
	sprite_.texture_coordinates(
		sanguis::client::draw2d::scene::background_texture_coordinates(
			sanguis::client::draw2d::translation{
				_translation.get()
				/
				fcppt::literal<
					sanguis::client::draw2d::unit
				>(
					2
				)
			},
			client_system_.renderer(),
			texture_
		)
	);

	client_system_.render(
		_render_context,
		sanguis::client::draw2d::sprite::client::category::background
	);
}

void
sanguis::client::draw2d::scene::background::reset_viewport()
{
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
