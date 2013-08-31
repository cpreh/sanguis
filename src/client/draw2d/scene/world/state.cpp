#include <sanguis/client/world_parameters.hpp>
#include <sanguis/client/draw2d/collide_parameters.hpp>
#include <sanguis/client/draw2d/optional_speed.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/batch_size.hpp>
#include <sanguis/client/draw2d/scene/world/generate_batches.hpp>
#include <sanguis/client/draw2d/scene/world/state.hpp>
#include <sanguis/client/draw2d/scene/world/tile_size.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/scale.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/top_result.hpp>
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
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/grid/clamp_signed_pos.hpp>
#include <fcppt/container/grid/make_pos_crange_start_end.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/ceil_div_signed.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::client::draw2d::scene::world::state::state(
	sge::renderer::device::core &_renderer,
	sanguis::load::tiles::context &_tiles,
	sanguis::client::world_parameters const &_parameters
)
:
	sanguis::client::draw2d::scene::world::state::state(
		_renderer,
		_tiles,
		sanguis::creator::generate(
			_parameters.top_parameters()
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

	sanguis::creator::difference_type const batch_size_trans(
		fcppt::cast::to_signed(
			sanguis::client::draw2d::scene::world::batch_size::value
			*
			sanguis::client::draw2d::scene::world::tile_size::value
		)
	);

	sanguis::creator::signed_pos const
		int_translation(
			fcppt::math::vector::structure_cast<
				sanguis::creator::signed_pos
			>(
				-_translation
			)
		);

	sanguis::client::draw2d::scene::world::batch_grid::pos const
		lower(
			fcppt::container::grid::clamp_signed_pos(
				int_translation
				/
				batch_size_trans,
				batches_.size()
			)
		),
		upper(
			fcppt::container::grid::clamp_signed_pos(
				fcppt::math::vector::ceil_div_signed(
					int_translation
					+
					fcppt::math::dim::structure_cast<
						sanguis::creator::signed_pos
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

sanguis::client::draw2d::optional_speed const
sanguis::client::draw2d::scene::world::state::test_collision(
	sanguis::client::draw2d::collide_parameters const &_parameters
) const
{
	sanguis::collision::optional_result const result(
		sanguis::collision::test_move(
			sanguis::collision::center(
				_parameters.center().get()
			),
			fcppt::math::dim::structure_cast<
				sanguis::collision::dim2
			>(
				_parameters.size()
			)
			/
			fcppt::cast::int_to_float<
				sanguis::collision::unit
			>(
				sanguis::collision::scale()
			),
			sanguis::collision::speed(
				_parameters.speed().get()
			),
			_parameters.duration(),
			grid_
		)
	);

	return
		result
		?
			sanguis::client::draw2d::optional_speed(
				sanguis::client::draw2d::speed(
					result->speed().get()
				)
			)
		:
			sanguis::client::draw2d::optional_speed()
		;
}

sanguis::client::draw2d::scene::world::state::state(
	sge::renderer::device::core &_renderer,
	sanguis::load::tiles::context &_tiles,
	sanguis::creator::top_result const &_result
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
		_result.grid()
	),
	batches_(
		sanguis::client::draw2d::scene::world::generate_batches(
			grid_,
			_result.background_grid(),
			_tiles,
			sprite_buffers_
		)
	)
{
}
