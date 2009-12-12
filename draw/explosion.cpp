#include "explosion.hpp"
#include "environment.hpp"
#include "particle/generator.hpp"
#include "particle/explosion.hpp"
#include "particle/properties.hpp"
#include "particle/object.hpp"
#include "particle/z_ordering.hpp"
#include "../load/context.hpp"
#include "../load/resource/sounds.hpp"
#include "../load/sound_type.hpp"
#include "../load/model/part.hpp"
#include "../load/model/weapon_category.hpp"
#include "../load/model/model.hpp"
#include "../load/model/context.hpp"
#include "../load/model/collection.hpp"
#include "../client/next_id.hpp"
#include "../resolution.hpp"
#include "../media_path.hpp"
#include "../animation_type.hpp"
#include "../from_particle_type.hpp"
#include <sge/math/vector/structure_cast.hpp>
#include <sge/minmax_pair_impl.hpp>
#include <sge/audio/sound.hpp>
#include <boost/assign/list_of.hpp>
#include <tr1/functional>

namespace
{

// TODO: put this somewhere else
sanguis::draw::particle::property_container const prop_ = boost::assign::map_list_of
(
	sanguis::particle_type::flare,
	sanguis::draw::particle::properties(
		static_cast<
			sanguis::draw::funit
		>(
			0.03),
		5,
		0,
		0,
		sanguis::draw::particle::align_type::random,
		sanguis::draw::particle::properties::dispersion_range(
			0,
			50),
		sanguis::draw::particle::properties::speed_range(
			0,
			0),
		sanguis::draw::particle::properties::rot_speed_range(
			0,
			10),
		false,
		sanguis::draw::particle::properties::fade_range(
			0,
			0),
		sanguis::draw::particle::movement_type::random)
)
(
	sanguis::particle_type::smoke,
	sanguis::draw::particle::properties(
		static_cast<
			sanguis::draw::funit
		>(
			0.04),
		9,
		0,
		0,
		sanguis::draw::particle::align_type::to_center,
		sanguis::draw::particle::properties::dispersion_range(
			0,
			20),
		sanguis::draw::particle::properties::speed_range(
			100,
			250),
		sanguis::draw::particle::properties::rot_speed_range(
			0,
			0),
		true,
		sanguis::draw::particle::properties::fade_range(
			2,
			10),
		sanguis::draw::particle::movement_type::expanding)
)
(
	sanguis::particle_type::rubble,
	sanguis::draw::particle::properties(
		static_cast<
			sanguis::draw::funit
		>(
			0.03),
		0,
		0,
		0,
		sanguis::draw::particle::align_type::random,
		sanguis::draw::particle::properties::dispersion_range(
			0,
			40),
		sanguis::draw::particle::properties::speed_range(
			0,
			400),
		sanguis::draw::particle::properties::rot_speed_range(
			0,
			10),
		false,
		sanguis::draw::particle::properties::fade_range(
			0,
			0),
		sanguis::draw::particle::movement_type::random)
)
;

}

sanguis::draw::explosion::explosion(
	draw::environment const &env,
	sprite::point const &pos_,
	funit const _aoe)
:
	entity(
		env,
		client::next_id()),
	pos_(pos_),
	particles(
		particle::point::null(),
		particle::point::null(),
		particle::depth(0),
		particle::rotation(0),
		particle::rotation(0),
		environment()),
	properties_(
		prop_),
	ended(
		false),
	aoe_(
		_aoe)
{
	// TODO: we have to pass the aoe here!
	sge::renderer::screen_size const screen_sz(
		resolution()
	);

	particle::base_ptr n(
		new particle::explosion(
			properties_,
			std::tr1::bind(
				&explosion::generate_particle,
				this,
				std::tr1::placeholders::_1
			),
			particle::point::null(), // pos
			//sge::math::structure_cast<
			//	particle::point::value_type
			//>(pos), // position
			particle::point::null(), // speed
			static_cast<particle::depth>(0),
			static_cast<particle::rotation>(0), // no rotation and...
			static_cast<particle::rotation>(0), // ...no rotation speed
			environment()
		)
	);

	particles.add(n);
}

sanguis::draw::explosion::~explosion()
{}

void sanguis::draw::explosion::update(
	time_type const delta)
{
	ended = particles.update(
		delta,
		sge::math::vector::structure_cast<
			particle::point
		>(pos_),
		//particle::point::null(),
		static_cast<particle::rotation>(0),
		static_cast<particle::depth>(0));
}

sanguis::draw::particle::base_ptr
sanguis::draw::explosion::generate_explosion()
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
			static_cast<particle::rotation>(0), // ...no rotation speed
			environment()));
}

sanguis::draw::particle::base_ptr
sanguis::draw::explosion::generate_particle(
	particle_type::type const t)
{
	load::model::animation::context_ptr anim = 
		environment().context().models()()
		[
			SGE_TEXT("particles/")+
			from_particle_type(t)
		]
		.random_part()
		[
			weapon_type::none
		]
		[
			animation_type::none
		].load();
	
	particle::base_ptr ptr;
	
	particle::properties const &prop(
		properties_[t]);

	if (!prop.do_fade())
		ptr.reset(
			new particle::object(
				t,
				aoe_,
				anim,
				boost::none,
				environment()));
	else
	{
		// FIXME: this should not be here!
		sge::random::uniform<
			particle::time_type
		>
			rng(
				particle::fade_time_range(
					prop.fade().min(),
					prop.fade().max()));
		
		ptr.reset(
			new particle::object(
				t,
				aoe_,
				anim,
				rng(),
				environment()));
	}

	/*
	ptr->depth(
		particle::z_ordering(t));
		*/

	return ptr;
}

bool sanguis::draw::explosion::may_be_removed() const
{
	return ended;
}
