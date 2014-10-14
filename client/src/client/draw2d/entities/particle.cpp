#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/particle.hpp>
#include <sanguis/client/draw2d/entities/particle_name.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/float_unit.hpp>
#include <sanguis/client/draw2d/sprite/optional_dim.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/parameters.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/animation.hpp>
#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sanguis/client/load/model/part.hpp>
#include <sanguis/client/load/model/weapon_category.hpp>
#include <sanguis/load/model/path.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::particle::particle(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::client::draw2d::entities::particle_name const &_name,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sanguis::client::load::model::collection const &_model_collection,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::optional_dim const _size
)
:
	sanguis::client::draw2d::entities::own(),
	ended_{
		false
	},
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
			fcppt::from_optional(
				_size,
				[]
				{
					return
						sanguis::client::draw2d::sprite::dim::null();
				}
			)
		)
		.texture(
			sanguis::client::draw2d::sprite::normal::object::texture_type{}
		)
		.any_color(
			sge::image::color::predef::white()
		)
	),
	animation_(
		_model_collection[
			sanguis::load::model::path{
				boost::filesystem::path{
					FCPPT_TEXT("particles")
				}
				/
				_name.get()
			}
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
	// TODO: Improve this
	if(
		!_size
	)
		sprite_.size(
			fcppt::math::dim::structure_cast<
				sanguis::client::draw2d::sprite::dim
			>(
				animation_.series().entities().back().texture().area().size()
			)
		);
}

sanguis::client::draw2d::entities::particle::~particle()
{
}

void
sanguis::client::draw2d::entities::particle::update()
{
	ended_ =
		animation_.process();
}

bool
sanguis::client::draw2d::entities::particle::may_be_removed() const
{
	return
		ended_;
}
