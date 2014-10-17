#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
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
#include <sanguis/client/load/resource/animation/series.hpp>
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
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::client::draw2d::entities::particle_name const &_name,
	sanguis::client::draw2d::z_ordering const _z_ordering,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::optional_dim const _size
)
:
	sanguis::client::draw2d::entities::particle{
		_load_parameters,
		_z_ordering,
		_center,
		_size,
		_load_parameters.collection()[
			sanguis::load::model::path{
				boost::filesystem::path{
					FCPPT_TEXT("particles")
				}
				/
				_name.get()
			}
		].random_part(
			_load_parameters.random_generator()
		)
		[
			sanguis::optional_primary_weapon_type()
		][
			sanguis::client::load::animation_type::none
		]
		.series()
	}
{
}

sanguis::client::draw2d::entities::particle::~particle()
{
}

sanguis::client::draw2d::entities::particle::particle(
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::client::draw2d::z_ordering const _z_ordering,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::optional_dim const _size,
	sanguis::client::load::resource::animation::series const &_animation_series
)
:
	sanguis::client::draw2d::entities::own(),
	ended_{
		false
	},
	sprite_(
		sanguis::client::draw2d::sprite::normal::parameters()
		.connection(
			_load_parameters.normal_system().connection(
				_z_ordering
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
				[
					&_animation_series
				]
				{
					return
						fcppt::math::dim::structure_cast<
							sanguis::client::draw2d::sprite::dim
						>(
							// TODO: Make this easier
							_animation_series.entities().back().texture().area().size()
						);
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
		_animation_series,
		sanguis::client::draw2d::sprite::animation::loop_method::stop_at_end,
		sprite_,
		_load_parameters.diff_clock()
	)
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
