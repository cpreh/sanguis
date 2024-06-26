#include <sanguis/exception.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/world_parameters.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/collide_parameters.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/optional_speed.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/translation_fwd.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/world/base.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/batch_size.hpp>
#include <sanguis/client/draw2d/scene/world/create.hpp>
#include <sanguis/client/draw2d/scene/world/generate_batches.hpp>
#include <sanguis/client/draw2d/scene/world/log_location.hpp>
#include <sanguis/client/draw2d/scene/world/parameters_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/state.hpp>
#include <sanguis/client/draw2d/scene/world/tile_size.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/state.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/unit.hpp>
#include <sanguis/client/load/tiles/context_ref.hpp>
#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/name_fwd.hpp>
#include <sanguis/creator/optional_background_tile.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/boost_units_value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/clamped_min.hpp>
#include <fcppt/container/grid/clamped_sup_signed.hpp>
#include <fcppt/container/grid/make_pos_ref_crange_start_end.hpp>
#include <fcppt/container/grid/min_from_pos.hpp>
#include <fcppt/container/grid/sup_from_pos.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/ceil_div_signed.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_signed.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::scene::world::state::state(
    fcppt::log::context_reference const _log_context,
    sanguis::random_generator &_random_generator,
    sge::renderer::device::core_ref const _renderer,
    sanguis::client::load::tiles::context_ref const _tiles,
    sanguis::client::draw::debug const _debug,
    sanguis::client::world_parameters const &_parameters,
    sanguis::client::draw2d::scene::world::parameters const &_world_parameters)
    : sanguis::client::draw2d::scene::world::state::state(
          _log_context,
          _random_generator,
          _renderer,
          _tiles,
          _debug,
          sanguis::creator::generate(_parameters.top_parameters()),
          _parameters.top_parameters().name(),
          _world_parameters)
{
}

sanguis::client::draw2d::scene::world::state::~state() = default;

void sanguis::client::draw2d::scene::world::state::update(
    sanguis::client::slowed_duration const _slowed_duration)
{
  effects_->update(_slowed_duration);
}

void sanguis::client::draw2d::scene::world::state::draw(
    sge::renderer::context::core &_render_context,
    sanguis::client::draw2d::translation const &_translation)
{
  if (batches_.empty())
  {
    return;
  }

  sanguis::creator::difference_type const batch_size_trans(fcppt::cast::to_signed(
      sanguis::client::draw2d::scene::world::batch_size::value *
      sanguis::client::draw2d::scene::world::tile_size::value));

  auto const int_translation(
      fcppt::math::vector::structure_cast<sanguis::creator::signed_pos, fcppt::cast::size_fun>(
          -_translation.get()));

  fcppt::container::grid::min_from_pos<sanguis::client::draw2d::scene::world::batch_grid::pos> const
      lower(fcppt::container::grid::clamped_min(
          ((int_translation -
            fcppt::math::vector::fill<sanguis::creator::signed_pos>(
                sanguis::client::draw2d::scene::world::tile_size::value /
                fcppt::literal<sanguis::client::draw2d::scene::world::sprite::unit>(2))) /
           batch_size_trans)
              .get_unsafe()));

  fcppt::container::grid::sup_from_pos<sanguis::client::draw2d::scene::world::batch_grid::pos> const
      upper(fcppt::container::grid::clamped_sup_signed(
          fcppt::optional::to_exception(
              fcppt::math::vector::ceil_div_signed(
                  int_translation +
                      fcppt::math::vector::structure_cast<
                          sanguis::creator::signed_pos,
                          fcppt::cast::size_fun>(
                          fcppt::math::vector::to_signed(fcppt::math::dim::to_vector(
                              sanguis::client::draw2d::scene::background_dim(renderer_.get())))),
                  batch_size_trans),
              [] { return sanguis::exception{FCPPT_TEXT("Zero batch size!")}; }),
          batches_.size()));

  sge::renderer::vertex::scoped_declaration const scoped_decl(
      fcppt::make_ref(_render_context), fcppt::make_cref(sprite_buffers_.vertex_declaration()));

  for (auto const entry :
       fcppt::container::grid::make_pos_ref_crange_start_end(batches_, lower, upper))
  {
    entry.value().draw(_render_context, sprite_buffers_.vertex_declaration(), sprite_state_);
  }
}

void sanguis::client::draw2d::scene::world::state::draw_after(
    sanguis::client::draw2d::scene::world::render_parameters const &_render_parameters)
{
  effects_->draw_after(_render_parameters);
}

sanguis::client::draw2d::optional_speed
sanguis::client::draw2d::scene::world::state::test_collision(
    sanguis::client::draw2d::collide_parameters const &_parameters) const
{
  return fcppt::optional::map(
      sanguis::collision::test_move(
          sanguis::collision::center{fcppt::math::vector::map(
              _parameters.center().get(),
              [](sanguis::client::draw2d::funit const _val)
              { return _val * boost::units::si::meter; })},
          sanguis::collision::radius(_parameters.radius().get() * boost::units::si::meter),
          fcppt::math::vector::map(
              _parameters.speed().get(),
              [](sanguis::client::draw2d::funit const _val)
              { return _val * boost::units::si::meter_per_second; }),
          _parameters.duration(),
          grid_),
      [](sanguis::collision::result const &_result)
      {
        return sanguis::client::draw2d::speed(
            fcppt::math::vector::map(_result.speed(), fcppt::boost_units_value{}));
      });
}

sanguis::creator::optional_background_tile
sanguis::client::draw2d::scene::world::state::background_tile(
    sanguis::creator::pos const &_pos) const
{
  return fcppt::optional::copy_value(fcppt::container::grid::at_optional(background_grid_, _pos));
}

sanguis::client::draw2d::scene::world::state::state(
	fcppt::log::context_reference const _log_context,
	sanguis::random_generator &_random_generator,
	sge::renderer::device::core_ref const _renderer,
	sanguis::client::load::tiles::context_ref const _tiles,
	sanguis::client::draw::debug const _debug,
	sanguis::creator::top_result const &_result,
	sanguis::creator::name const &_name,
	sanguis::client::draw2d::scene::world::parameters const &_parameters
)
:
	log_{
		_log_context,
		sanguis::client::draw2d::scene::world::log_location(),
		// TODO(philipp): Add world name?
			fcppt::log::name{
				FCPPT_TEXT("state")
			}
	},
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
	background_grid_{
		_result.background_grid()
	},
	batches_(
		sanguis::client::draw2d::scene::world::generate_batches(
			_log_context,
			_random_generator,
			_debug,
			grid_,
			_result.background_grid(),
			_tiles,
			fcppt::make_ref(
				sprite_buffers_
			)
		)
	),
	effects_{
		sanguis::client::draw2d::scene::world::create(
			log_,
			_name,
			_parameters
		)
	}
{
}
