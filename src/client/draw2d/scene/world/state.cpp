#include <sanguis/collision_scale.hpp>
#include <sanguis/client/world_parameters.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/batch_size.hpp>
#include <sanguis/client/draw2d/scene/world/ceil_div_signed_pos.hpp>
#include <sanguis/client/draw2d/scene/world/clamp_pos.hpp>
#include <sanguis/client/draw2d/scene/world/generate_batches.hpp>
#include <sanguis/client/draw2d/scene/world/signed_pos.hpp>
#include <sanguis/client/draw2d/scene/world/state.hpp>
#include <sanguis/client/draw2d/scene/world/tile_size.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/result.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/load/tiles/context_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/one_with_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/grid/make_pos_crange_start_end.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::client::draw2d::scene::world::state::state(
	sge::renderer::device::core &_renderer,
	sanguis::load::tiles::context &_tiles,
	sanguis::client::world_parameters const &_parameters
)
:
	renderer_(
		_renderer
	),
	sprite_buffers_(
		_renderer,
		sge::sprite::buffers::option::static_
	),
	sprite_state_(
		renderer_,
		sanguis::client::draw2d::scene::world::sprite::state::parameters_type()
	),
	grid_(
		sanguis::creator::generate(
			_parameters.top_parameters()
		).grid()
	),
	batches_(
		sanguis::client::draw2d::scene::world::generate_batches(
			grid_,
			_tiles,
			sprite_buffers_
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
		batches_.empty()
	)
		return;

	sanguis::client::draw2d::scene::world::signed_pos::value_type const batch_size_trans(
		static_cast<
			sanguis::client::draw2d::scene::world::signed_pos::value_type
		>(
			sanguis::client::draw2d::scene::world::batch_size::value
			*
			sanguis::client::draw2d::scene::world::tile_size::value
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
				batch_size_trans,
				batches_.size()
			)
		),
		upper(
			sanguis::client::draw2d::scene::world::clamp_pos(
				sanguis::client::draw2d::scene::world::ceil_div_signed_pos(
					int_translation
					+
					fcppt::math::dim::structure_cast<
						sanguis::client::draw2d::scene::world::signed_pos
					>(
						sanguis::client::draw2d::scene::background_dim(
							renderer_
						)
					),
					batch_size_trans
				),
				batches_.size()
			)
		);

	FCPPT_ASSERT_ERROR(
		lower <= upper
	);

	sge::renderer::vertex::scoped_declaration const scoped_decl(
		_render_context,
		sprite_buffers_.parameters().vertex_declaration()
	);

	for(
		auto const &entry
		:
		fcppt::container::grid::make_pos_crange_start_end(
			batches_,
			lower,
			upper
		)
	)
		entry.value().draw(
			_render_context,
			sprite_buffers_.parameters().vertex_declaration(),
			sprite_state_
		);
}

bool
sanguis::client::draw2d::scene::world::state::test_collision(
	sanguis::client::draw2d::sprite::center const &_center,
	sanguis::client::draw2d::sprite::dim const &_dim
) const
{
	sanguis::client::draw2d::sprite::dim const scaled_dim(
		_dim
		/
		static_cast<
			sanguis::client::draw2d::sprite::unit
		>(
			sanguis::collision_scale()
		)
	);

	sanguis::client::draw2d::scene::world::batch_grid::dim const lower(
		sanguis::client::draw2d::scene::world::clamp_pos(
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::scene::world::signed_pos
			>(
				(
					_center.get() - scaled_dim / 2
				)
				/
				sanguis::client::draw2d::scene::world::tile_size::value
			),
			grid_.size()
		)
	);

	sanguis::client::draw2d::scene::world::batch_grid::dim const upper(
		sanguis::client::draw2d::scene::world::clamp_pos(
			sanguis::client::draw2d::scene::world::ceil_div_signed_pos(
				fcppt::math::vector::structure_cast<
					sanguis::client::draw2d::scene::world::signed_pos
				>(
					_center.get() + scaled_dim / 2
				),
				sanguis::client::draw2d::scene::world::tile_size::value
			),
			grid_.size()
		)
	);

	FCPPT_ASSERT_ERROR(
		lower <= upper
	);

	for(
		auto const &entry
		:
		fcppt::container::grid::make_pos_crange_start_end(
			grid_,
			lower,
			upper
		)
	)
		if(
			sanguis::creator::tile_is_solid(
				entry.value()
			)
		)
			return true;

	return false;
}
