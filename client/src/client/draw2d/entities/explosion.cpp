#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/particle.hpp>
#include <sanguis/client/draw2d/entities/particle_name.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/optional_dim.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/math/dim/fill.hpp>


sanguis::client::draw2d::entities::explosion::explosion(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sanguis::client::load::model::collection const &_model_collection,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::aoe const _aoe
)
:
	sanguis::client::draw2d::entities::particle{
		_diff_clock,
		_random_generator,
		sanguis::client::draw2d::entities::particle_name{
			FCPPT_TEXT("flare")
		},
		_normal_system,
		_model_collection,
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
						1.5
					)
				)
			)
		}
	}
{
}

sanguis::client::draw2d::entities::explosion::~explosion()
{
}
