#include "simple.hpp"
#include "../entities/enemies/factory.hpp"
#include "../environment.hpp"
#include "../../random.hpp"
#include "../../angle_vector.hpp"
#include "../../resolution.hpp"
#include <sge/time/second.hpp>
#include <sge/math/constants.hpp>
#include <boost/tr1/random.hpp>
#include <algorithm>

sanguis::server::waves::simple::simple(
	time_type const spawn_interval,
	unsigned const total_spawn_count,
	enemy_type::type const etype)
: diff_(),
  spawn_timer(
  	sge::time::second(
		spawn_interval),
	true,
	diff_.callback()),
  total_spawn_count(total_spawn_count),
  etype(etype),
  spawn_count(0)
{}

void sanguis::server::waves::simple::process(
	time_type const diff,
	environment const &env)
{
	diff_.update(diff);
	if(!spawn_timer.update_b())
		return;

	if(spawn_count == total_spawn_count)
		return;
	++spawn_count;

	typedef std::tr1::uniform_real<
		messages::space_unit
	> uniform_su;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		uniform_su
	> rng_type;

	static rng_type rng(
		create_seeded_randgen(),
		uniform_su(
			messages::mu(0),
			sge::math::twopi<messages::space_unit>()
		));

	sge::renderer::screen_size_t const res(
		resolution());

	messages::space_unit const
		rand_angle(rng()),
		radius(
			messages::mu(
				std::max(
					res.w(),
					res.h()))
			/ messages::mu(2)),
		scale(messages::mu(1.5)),
		angle(messages::mu(0));
	
	messages::pos_type const
		screen_center(
			messages::pos_type(
				messages::mu(res.w()),
				messages::mu(res.h()))
			/ messages::mu(2)),
		center(
			scale * radius * angle_to_vector(rand_angle)),
		pos(
			center + screen_center);

	env.insert(
		entities::enemies::create(
			etype,
			env,
			pos,
			angle,
			angle));
}

bool sanguis::server::waves::simple::ended() const
{
	return spawn_count == total_spawn_count;
}
