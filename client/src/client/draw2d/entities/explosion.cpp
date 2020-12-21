#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/particle.hpp>
#include <sanguis/client/draw2d/entities/particle_name.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/optional_dim.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/math/dim/fill.hpp>


sanguis::client::draw2d::entities::explosion::explosion(
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::client::draw2d::sprite::center const &_center,
	sanguis::client::draw2d::aoe const _aoe
)
:
	sanguis::client::draw2d::entities::particle{
		_load_parameters,
		sanguis::client::draw2d::entities::particle_name{
			FCPPT_TEXT("flare")
		},
		sanguis::client::draw2d::z_ordering::flare,
		_center,
		sanguis::client::draw2d::sprite::optional_dim{
			fcppt::math::dim::fill<
				sanguis::client::draw2d::sprite::dim
			>(
				fcppt::cast::float_to_int<
					sanguis::client::draw2d::sprite::unit
				>(
					_aoe.get()
					*
					fcppt::literal<
						sanguis::client::draw2d::funit
					>(
						1.5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
					)
				)
			)
		}
	}
{
}

sanguis::client::draw2d::entities::explosion::~explosion()
= default;
