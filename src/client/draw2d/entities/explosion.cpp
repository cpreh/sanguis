#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/explosion_particle.hpp>
#include <sanguis/client/draw2d/entities/explosion_properties.hpp>
#include <sanguis/client/draw2d/particle/explosion.hpp>
#include <sanguis/client/draw2d/particle/depth.hpp>
#include <sanguis/client/draw2d/particle/fade_time_range.hpp>
#include <sanguis/client/draw2d/particle/properties.hpp>
#include <sanguis/client/draw2d/particle/rotation.hpp>
#include <sanguis/client/draw2d/particle/z_ordering.hpp>
#include <sanguis/client/draw2d/particle/type_to_string.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/load/model/animation/object.hpp>
#include <sanguis/load/model/animation/context.hpp>
#include <sanguis/load/model/collection.hpp>
#include <sanguis/load/model/object.hpp>
#include <sanguis/load/model/part.hpp>
#include <sanguis/load/model/weapon_category.hpp>
#include <sanguis/animation_type.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/minmax_pair_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::explosion::explosion(
	sanguis::diff_clock const &_diff_clock,
	sprite::particle::system &_particle_system,
	load::model::collection const &_model_collection,
	sprite::center const &_center,
	draw2d::aoe const _aoe
)
:
	entities::own(),
	diff_clock_(_diff_clock),
	particle_system_(
		_particle_system
	),
	model_collection_(
		_model_collection
	),
	particles_(
		_diff_clock,
		draw2d::center(
			fcppt::math::vector::structure_cast<
				draw2d::center::value_type
			>(
				_center.get()
			)
		),
		draw2d::speed(
			draw2d::speed::value_type::null()
		),
		particle::depth(
			0
		),
		particle::rotation(
			0
		),
		particle::rotation_speed(
			0
		)
	),
	properties_(
		entities::explosion_properties()
	),
	aoe_(
		_aoe
	),
	ended_(
		false
	)
{
	particles_.add(
		this->generate_explosion()
	);
}

sanguis::client::draw2d::entities::explosion::~explosion()
{
}

void
sanguis::client::draw2d::entities::explosion::update()
{
	ended_ =
		particles_.update(
			draw2d::center(
				draw2d::center::value_type::null()
			),
			particle::rotation(
				0
			),
			particle::depth(
				0
			)
		);
}

bool
sanguis::client::draw2d::entities::explosion::may_be_removed() const
{
	return ended_;
}

sanguis::client::draw2d::particle::base_ptr
sanguis::client::draw2d::entities::explosion::generate_explosion()
{
	return
		particle::base_ptr(
			fcppt::make_unique_ptr<
				particle::explosion
			>(
				fcppt::cref(
					diff_clock_
				),
				properties_,
				std::tr1::bind(
					&explosion::generate_particle,
					this,
					std::tr1::placeholders::_1
				),
				draw2d::center(
					draw2d::center::value_type::null()
				),
				draw2d::speed(
					draw2d::speed::value_type::null()
				),
				particle::depth(0),
				particle::rotation(0),
				particle::rotation_speed(0)
			)
		);
}

sanguis::client::draw2d::particle::base_ptr
sanguis::client::draw2d::entities::explosion::generate_particle(
	particle::particle_type::type const _particle_type
)
{
	particle::base_ptr ptr(
		entities::explosion_particle(
			diff_clock_,
			_particle_type,
			particle_system_,
			aoe_,
			properties_[
				_particle_type
			],
			model_collection_
			[
				FCPPT_TEXT("particles/")
				+
				particle::type_to_string(
					_particle_type
				)
			]
			.random_part()
			[
				weapon_type::none
			]
			[
				animation_type::none
			].load()
		)
	);

	ptr->depth(
		particle::depth(
			particle::z_ordering(
				_particle_type
			)
		)
	);

	return
		move(
			ptr
		);
}
