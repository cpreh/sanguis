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
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/world_parameters.hpp>
#include <sge/renderer/clear_flags.hpp>
#include <sge/renderer/clear_flags_field.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/stencil_op.hpp>
#include <sge/renderer/state/stencil_op_value.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/render_one_advanced.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/grid/object_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/transform.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/round_div_int.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::client::draw2d::scene::world::state::state(
	sge::renderer::device &_renderer,
	load::resource::textures const &_textures,
	sge::renderer::vertex_declaration const &_vertex_declaration,
	client::world_parameters const &_parameters
)
:
	renderer_(_renderer),
	vertex_declaration_(_vertex_declaration),
	batches_(
		world::generate_batches(
			_renderer,
			_vertex_declaration,
			_parameters.top_parameters(),
			_textures
		)
	),
	stencil_sprite_system_(
		renderer_
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
					world::batch_size
				)
			)
		)
		.elements()
	)
{
}

sanguis::client::draw2d::scene::world::state::~state()
{
}

void
sanguis::client::draw2d::scene::world::state::draw(
	draw2d::vector2 const &_translation
)
{
	if(
		batches_->empty()
	)
		return;

	sge::renderer::screen_size const viewport_size(
		sge::renderer::viewport_size(
			renderer_
		)
	);

	world::signed_pos::value_type const batch_size_trans(
		static_cast<
			world::signed_pos::value_type
		>(
			world::batch_size
		)
	);

	world::signed_pos const
		int_translation(
			fcppt::math::vector::structure_cast<
				world::signed_pos
			>(
				-_translation
			)
		);

	world::batch_grid::dim const
		lower(
			world::clamp_pos(
				int_translation
				/
				batch_size_trans
				,
				batches_->size()
			)
		),
		upper(
			world::clamp_pos(
				fcppt::math::dim::transform(
					(
						int_translation
						+
						fcppt::math::dim::structure_cast<
							world::signed_pos
						>(
							scene::background_dim(
								renderer_
							)
						)
					),
					std::tr1::bind(
						fcppt::math::round_div_int<
							batch_grid::size_type
						>,
						std::tr1::placeholders::_1,
						batch_size_trans
					)
				),
				batches_->size()
			)
		);

	sge::renderer::state::scoped const scoped_state(
		renderer_,
		sge::renderer::state::list
		(
			sge::renderer::state::stencil_func::equal
		)
		(
			sge::renderer::state::int_::stencil_ref = 0
		)
		(
			sge::renderer::state::int_::stencil_buffer_clear_val = 0
		)
		(
			sge::renderer::state::bool_::enable_alpha_blending = true
		)
		(
			sge::renderer::state::source_blend_func::src_alpha
		)
		(
			sge::renderer::state::dest_blend_func::inv_src_alpha
		)
	);

	renderer_.clear(
		sge::renderer::clear_flags_field(
			sge::renderer::clear_flags::stencil_buffer
		)
	);

	FCPPT_ASSERT_ERROR(
		lower <= upper
	);

	for(
		batch_grid::size_type pos_y(
			lower.h()
		);
		pos_y != upper.h();
		++pos_y
	)
		for(
			batch_grid::size_type pos_x(
				lower.w()
			);
			pos_x != upper.w();
			++pos_x
		)
		{
			batch_grid::dim const pos(
				pos_x,
				pos_y
			);

			sge::renderer::scoped_vertex_declaration const scoped_decl(
				renderer_,
				vertex_declaration_
			);

			(*batches_).at(
				pos
			).draw(
				renderer_
			);

			stencil_sprite_.pos(
				fcppt::math::dim::structure_cast<
					world::sprite::object::vector
				>(
					pos
				)
				* stencil_sprite_.size()
			);

			{
				sge::renderer::state::scoped const scoped_state_inner(
					renderer_,
					sge::renderer::state::list
					(
						sge::renderer::state::stencil_func::never
					)
					(
						sge::renderer::state::stencil_op::stencil_fail
							= sge::renderer::state::stencil_op_value::inc_sat
					)
				);

				sge::sprite::render_one_advanced(
					stencil_sprite_system_,
					stencil_sprite_
				);
			}
		}
}
