#include "state.hpp"
#include "batch.hpp"
#include "batch_grid.hpp"
#include "batch_size.hpp"
#include "clamp_pos.hpp"
#include "generate_batches.hpp"
#include "sprite/object.hpp"
#include "sprite/parameters.hpp"
#include "../../../world_parameters.hpp"
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
#include <sge/sprite/render_one.hpp>
#include <fcppt/container/grid/object_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
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
	sge::renderer::scoped_vertex_declaration const scoped_decl(
		renderer_,
		vertex_declaration_
	);
	
	sge::renderer::screen_size const viewport_size(
		sge::renderer::viewport_size(
			renderer_
		)
	);

	// translation is the middle of the screen, so the visible part is
	// (translation - viewport_size / 2, translation + viewport_size / 2)

	batch_grid::size_type const batch_size_trans(
		static_cast<
			batch_grid::size_type
		>(
			world::batch_size
		)
	);

	batch_grid::dim const
		int_translation(
			fcppt::math::vector::structure_cast<
				batch_grid::dim
			>(
				_translation
			)
		),
		half_viewport(
			fcppt::math::dim::structure_cast<
				batch_grid::dim
			>(
				viewport_size
			)
			/
			static_cast<
				batch_grid::size_type
			>(
				2
			)
		),
		lower(
			world::clamp_pos(
				(
					int_translation
					-
					half_viewport
				)
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
						half_viewport
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
					
				sge::sprite::render_one(
					stencil_sprite_system_,
					stencil_sprite_
				);
			}

			(*batches_)[
				pos
			].draw(
				renderer_
			);
		}
}
