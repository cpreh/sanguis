#include <sanguis/client/world_parameters.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/scene/world/state.hpp>
#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/batch_size.hpp>
#include <sanguis/client/draw2d/scene/world/clamp_pos.hpp>
#include <sanguis/client/draw2d/scene/world/generate_batches.hpp>
#include <sanguis/client/draw2d/scene/world/signed_pos.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/object.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/parameters.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/combined_simple.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/op.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/one_with_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <fcppt/algorithm/array_map.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/grid/object_impl.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::world::state::state(
	sge::renderer::device::core &_renderer,
	sanguis::load::resource::textures const &_textures,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sanguis::client::world_parameters const &_parameters
)
:
	renderer_(
		_renderer
	),
	vertex_declaration_(
		_vertex_declaration
	),
	batches_(
		sanguis::client::draw2d::scene::world::generate_batches(
			_renderer,
			_vertex_declaration,
			_parameters.top_parameters(),
			_textures
		)
	),
	stencil_sprite_buffers_(
		renderer_,
		sge::sprite::buffers::option::dynamic
	),
	stencil_sprite_states_(
		renderer_,
		sge::sprite::state::parameters<
			sanguis::client::draw2d::scene::world::sprite::state_choices
		>()
	),
	stencil_sprite_(
		world::sprite::parameters()
		.size(
			fcppt::math::dim::structure_cast<
				world::sprite::object::dim
			>(
				fcppt::math::dim::fill<
					2
				>(
					sanguis::client::draw2d::scene::world::batch_size::value
				)
			)
		)
	),
	batch_stencil_state_(
		renderer_.create_depth_stencil_state(
			sge::renderer::state::core::depth_stencil::parameters(
				sge::renderer::state::core::depth_stencil::depth::off(),
				sge::renderer::state::core::depth_stencil::stencil::combined_simple(
					sge::renderer::state::core::depth_stencil::stencil::func::equal
				)
				.to_enabled()
			)
		)
	),
	mask_stencil_state_(
		renderer_.create_depth_stencil_state(
			sge::renderer::state::core::depth_stencil::parameters(
				sge::renderer::state::core::depth_stencil::depth::off(),
				sge::renderer::state::core::depth_stencil::stencil::combined_simple(
					sge::renderer::state::core::depth_stencil::stencil::func::never
				)
				.fail_op(
					sge::renderer::state::core::depth_stencil::stencil::op::inc_sat
				)
				.to_enabled()
			)
		)
	)
{
}

sanguis::client::draw2d::scene::world::state::~state()
{
}

void
sanguis::client::draw2d::scene::world::state::draw(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::vector2 const &_translation
)
{
	if(
		batches_->empty()
	)
		return;

	sanguis::client::draw2d::scene::world::signed_pos::value_type const batch_size_trans(
		static_cast<
			sanguis::client::draw2d::scene::world::signed_pos::value_type
		>(
			sanguis::client::draw2d::scene::world::batch_size::value
		)
	);

	sanguis::client::draw2d::scene::world::signed_pos const
		int_translation(
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::scene::world::signed_pos
			>(
				-_translation
			)
		);

	sanguis::client::draw2d::scene::world::batch_grid::dim const
		lower(
			sanguis::client::draw2d::scene::world::clamp_pos(
				int_translation
				/
				batch_size_trans
				,
				batches_->size()
			)
		),
		upper(
			sanguis::client::draw2d::scene::world::clamp_pos(
				fcppt::algorithm::array_map<
					sanguis::client::draw2d::scene::world::signed_pos
				>(
					(
						int_translation
						+
						fcppt::math::dim::structure_cast<
							sanguis::client::draw2d::scene::world::signed_pos
						>(
							sanguis::client::draw2d::scene::background_dim(
								renderer_
							)
						)
					),
					std::bind(
						fcppt::math::ceil_div<
							sanguis::client::draw2d::scene::world::batch_grid::size_type
						>,
						std::placeholders::_1,
						batch_size_trans
					)
				),
				batches_->size()
			)
		);

	_render_context.clear(
		sge::renderer::clear::parameters()
		.stencil_buffer(
			0
		)
	);


	FCPPT_ASSERT_ERROR(
		lower <= upper
	);

	for(
		sanguis::client::draw2d::scene::world::batch_grid::size_type pos_y(
			lower.h()
		);
		pos_y <= upper.h();
		++pos_y
	)
		for(
			sanguis::client::draw2d::scene::world::batch_grid::size_type pos_x(
				lower.w()
			);
			pos_x <= upper.w();
			++pos_x
		)
		{
			sanguis::client::draw2d::scene::world::batch_grid::dim const pos(
				pos_x,
				pos_y
			);

			{
				sge::renderer::vertex::scoped_declaration const scoped_decl(
					_render_context,
					vertex_declaration_
				);

				sge::renderer::state::core::depth_stencil::scoped const scoped_stencil(
					_render_context,
					*batch_stencil_state_
				);

				sanguis::client::draw2d::scene::world::batch &batch(
					(*batches_).at(
						pos
					)
				);

				if(
					!batch.empty()
				)
					batch.draw(
						_render_context
					);
			}

			stencil_sprite_.pos(
				fcppt::math::dim::structure_cast<
					sanguis::client::draw2d::scene::world::sprite::object::vector
				>(
					pos
				)
				* stencil_sprite_.size()
			);

			{
				sge::renderer::state::core::depth_stencil::scoped const scoped_stencil(
					_render_context,
					*mask_stencil_state_
				);

				sge::sprite::process::one_with_options<
					sge::sprite::process::options<
						sge::sprite::process::geometry_options::update
					>
				>(
					_render_context,
					stencil_sprite_,
					stencil_sprite_buffers_,
					stencil_sprite_states_,
					sge::sprite::state::default_options<
						sanguis::client::draw2d::scene::world::sprite::state_choices
					>()
				);
			}
		}
}
