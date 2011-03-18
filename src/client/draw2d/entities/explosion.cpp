#include "explosion.hpp"
#include "explosion_properties.hpp"
#include "../particle/explosion.hpp"
#include "../particle/depth.hpp"
#include "../particle/fade_time_range.hpp"
#include "../particle/properties.hpp"
#include "../particle/object.hpp"
#include "../particle/point.hpp"
#include "../particle/rotation.hpp"
#include "../particle/z_ordering.hpp"
#include "../particle/type_to_string.hpp"
#include "../../../load/model/part.hpp"
#include "../../../load/model/weapon_category.hpp"
#include "../../../load/model/object.hpp"
#include "../../../load/model/collection.hpp"
#include "../../../load/model/animation.hpp"
#include "../../../load/model/animation_context.hpp"
#include "../../../animation_type.hpp"
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/minmax_pair_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::explosion::explosion(
	sprite::particle::system &_particle_system,
	load::model::collection const &_model_collection,
	sprite::point const &_pos,
	funit const _aoe
)
:
	base(),
	particle_system_(_particle_system),
	model_collection_(_model_collection),
	pos_(_pos),
	particles(
		particle::point::null(),
		particle::point::null(),
		particle::depth(0),
		particle::rotation(0),
		particle::rotation(0)
	),
	properties_(
		explosion_properties()
	),
	ended(
		false
	),
	aoe_(
		_aoe
	)
{
	particle::base_ptr n(
		new particle::explosion(
			properties_,
			std::tr1::bind(
				&explosion::generate_particle,
				this,
				std::tr1::placeholders::_1
			),
			particle::point::null(), // pos
			//fcppt::math::structure_cast<
			//	particle::point::value_type
			//>(pos), // position
			particle::point::null(), // speed
			static_cast<particle::depth>(0),
			static_cast<particle::rotation>(0), // no rotation and...
			static_cast<particle::rotation>(0)//, // ...no rotation speed
			//particle_system_
		)
	);

	particles.add(n);
}

sanguis::client::draw2d::entities::explosion::~explosion()
{}

void
sanguis::client::draw2d::entities::explosion::pos(
	sprite::point const &
)
{}

void
sanguis::client::draw2d::entities::explosion::dim(
	sprite::dim const &
)
{}

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::entities::explosion::center() const
{
	return pos_;
}

void
sanguis::client::draw2d::entities::explosion::update(
	time_type const delta
)
{
	ended =
		particles.update(
			delta,
			fcppt::math::vector::structure_cast<
				particle::point
			>(pos_),
			//particle::point::null(),
			static_cast<particle::rotation>(0),
			static_cast<particle::depth>(0)
		);
}

sanguis::client::draw2d::particle::base_ptr
sanguis::client::draw2d::entities::explosion::generate_explosion()
{
	return particle::base_ptr(
		new particle::explosion(
			properties_,
			std::tr1::bind(
				&explosion::generate_particle,
				this,
				std::tr1::placeholders::_1
			),
			particle::point::null(), // position
			particle::point::null(), // speed
			static_cast<particle::depth>(0),
			static_cast<particle::rotation>(0), // no rotation and...
			static_cast<particle::rotation>(0)  // ...no rotation speed
		)
	);
}

sanguis::client::draw2d::particle::base_ptr
sanguis::client::draw2d::entities::explosion::generate_particle(
	particle::particle_type::type const _particle_type
)
{
	load::model::animation_context_ptr anim(
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
	);
	
	particle::base_ptr ptr;
	
	particle::properties const &prop(
		properties_[
			_particle_type
		]
	);

	if(
		!prop.do_fade()
	)
		ptr.reset(
			new particle::object(
				_particle_type,
				aoe_,
				move(
					anim
				),
				particle::object::optional_time(),
				particle_system_
			)
		);
	else
	{
		// FIXME: this should not be here!
		fcppt::random::uniform<
			particle::time_type
		>
			rng(
				particle::fade_time_range(
					prop.fade().min(),
					prop.fade().max()
				)
			);
		
		ptr.reset(
			new particle::object(
				_particle_type,
				aoe_,
				move(
					anim
				),
				rng(),
				particle_system_
			)
		);
	}

	ptr->depth(
		particle::z_ordering(
			_particle_type
		)
	);

	return ptr;
}

bool
sanguis::client::draw2d::entities::explosion::is_decayed() const
{
	return ended;
}
