#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/buffs/burn.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
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
#include <sge/sprite/center.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/arithmetic.hpp>


sanguis::client::draw2d::entities::buffs::burn::burn(
	sanguis::diff_clock const &_diff_clock,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sanguis::client::load::model::collection const &_model_collection,
	sanguis::client::draw2d::entities::model::object const &_model
)
:
	sanguis::client::draw2d::entities::buffs::base(),
	sprite_(
		sanguis::client::draw2d::sprite::normal::parameters()
		.connection(
			_normal_system.connection(
				sanguis::client::draw2d::z_ordering::flare
			)
		)
		.center(
			_model.center().get()
		)
		.rotation(
			fcppt::literal<
				sanguis::client::draw2d::sprite::float_unit
			>(
				0
			)
		)
		.size(
			_model.master().size()
			/
			fcppt::literal<
				sanguis::client::draw2d::sprite::unit
			>(
				2
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
			FCPPT_TEXT("fire")
		][
			FCPPT_TEXT("default")
		]
		[
			sanguis::optional_primary_weapon_type()
		][
			sanguis::client::load::animation_type::none
		]
		.series(),
		sanguis::client::draw2d::sprite::animation::loop_method::repeat,
		sprite_,
		_diff_clock
	)
{
}

sanguis::client::draw2d::entities::buffs::burn::~burn()
{
}

void
sanguis::client::draw2d::entities::buffs::burn::update(
	sanguis::client::draw2d::entities::model::object const &_model
)
{
	sge::sprite::center(
		sprite_,
		_model.center().get()
	);

	animation_.process();
}
