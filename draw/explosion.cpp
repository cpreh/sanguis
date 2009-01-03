#include "explosion.hpp"
#include "environment.hpp"
#include "particle/generator.hpp"
#include "particle/explosion.hpp"
#include "particle/properties.hpp"
#include "particle/object.hpp"
#include "particle/z_ordering.hpp"
#include "../load/context.hpp"
#include "../load/particle/context.hpp"
#include "../load/particle/collection.hpp"
#include "../load/particle/animations.hpp"
#include "../load/particle/random_animation.hpp"
#include "../load/particle/animation.hpp"
#include "../client/next_id.hpp"
#include "../resolution.hpp"
#include <sge/minmax_pair_impl.hpp>
#include <boost/bind.hpp>
#include <boost/assign/list_of.hpp>

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
			10),
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
			0.03),
		8,
		0,
		0,
		sanguis::draw::particle::align_type::to_center,
		sanguis::draw::particle::properties::dispersion_range(
			0,
			50),
		sanguis::draw::particle::properties::speed_range(
			0,
			0),
		sanguis::draw::particle::properties::rot_speed_range(
			0,
			1),
		true,
		sanguis::draw::particle::properties::fade_range(
			4,
			6),
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
	sge::sprite::point const &pos_)
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
	ended(false)
{
	sge::renderer::screen_size_t const screen_sz(
		resolution());

	/*
	particle::base_ptr n(
		new particle::generator(
			boost::bind(
				&explosion::generate_explosion,
				this),
			sge::math::structure_cast<
				particle::point::value_type
			>(pos),
			static_cast<particle::time_type>(10),
			static_cast<particle::time_type>(1),
			1,
			particle::align_type::random,
			0,
			particle::dispersion_range(0,100),
			particle::velocity_range(0,30),
			particle::rotation_velocity_range(0,0),
			particle::movement_type::expanding,
			environment()
		));
		*/

	particle::base_ptr n(
		new particle::explosion(
			properties_,
			boost::bind(
				&explosion::generate_particle,
				this,
				_1),
			particle::point::null(), // pos
			//sge::math::structure_cast<
			//	particle::point::value_type
			//>(pos), // position
			particle::point::null(), // speed
			static_cast<particle::depth>(0),
			static_cast<particle::rotation>(0), // no rotation and...
			static_cast<particle::rotation>(0), // ...no rotation speed
			environment()));

	particles.add(n);

/*
	sge::audio::sound_ptr const s = 
		environment().context().resource().sounds().make(sys.audio_player()->create_nonstream_sound(
			sounds.random_file());
	
	s->positional(true);
	s->pos(
		sge::audio::point(
			pos.x(),
			0,
			pos.y()));
	
	s->rolloff(
		static_cast<sge::audio::unit>(1)
		/ static_cast<sge::audio::unit>(
			set.screen_size().h()));

	sound_pool->add(s);

	s->play(sge::audio::play_mode::once);*/

	//epilepsy_timer.reset();

}

sanguis::draw::explosion::~explosion()
{}

void sanguis::draw::explosion::update(
	time_type const delta)
{
	ended = particles.update(
		delta,
		sge::math::structure_cast<
			particle::point::value_type
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
			boost::bind(
				&explosion::generate_particle,
				this,
				_1),
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
	sge::sprite::animation_series const anim =
		environment().context().particles()()[t].random()().get();
	
	particle::base_ptr ptr;
	
	particle::properties const &prop(
		properties_[t]);

	if (!prop.do_fade())
		ptr.reset(
			new particle::object(
				t,
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
