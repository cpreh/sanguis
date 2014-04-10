#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/float_unit.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/parameters.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/texture_animation.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/animation.hpp>
#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sanguis/client/load/model/part.hpp>
#include <sanguis/client/load/model/weapon_category.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/math/dim/fill.hpp>


sanguis::client::draw2d::entities::explosion::explosion(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sanguis::client::load::model::collection const &_model_collection,
	sanguis::client::draw2d::sprite::center const &_center,
	sanguis::client::draw2d::aoe const _aoe
)
:
	sanguis::client::draw2d::entities::own(),
	ended_(
		false
	),
	sprite_(
		sanguis::client::draw2d::sprite::normal::parameters()
		.connection(
			_normal_system.connection(
				sanguis::client::draw2d::z_ordering::flare
			)
		)
		.center(
			_center.get()
		)
		.rotation(
			fcppt::literal<
				sanguis::client::draw2d::sprite::float_unit
			>(
				0
			)
		)
		.size(
			fcppt::math::dim::fill<
				sanguis::client::draw2d::sprite::dim::dim_wrapper::value
			>(
				fcppt::cast::float_to_int<
					sanguis::client::draw2d::sprite::unit
				>(
					_aoe.get()
					*
					fcppt::literal<
						sanguis::client::draw2d::funit
					>(
						2
					)
				)
			)
		)
		.texture(
			sge::texture::const_part_shared_ptr()
		)
		.any_color(
			sge::image::color::predef::white()
		)
	),
	animation_(
		_model_collection[
			FCPPT_TEXT("particles/flare")
		]
		.random_part(
			_random_generator
		)
		[
			sanguis::optional_primary_weapon_type()
		][
			sanguis::client::load::animation_type::none
		]
		.series(),
		sanguis::client::draw2d::sprite::animation::loop_method::stop_at_end,
		sprite_,
		_diff_clock
	)
{
}

sanguis::client::draw2d::entities::explosion::~explosion()
{
}

void
sanguis::client::draw2d::entities::explosion::update()
{
	ended_ =
		animation_.process();
}

bool
sanguis::client::draw2d::entities::explosion::may_be_removed() const
{
	return ended_;
}
