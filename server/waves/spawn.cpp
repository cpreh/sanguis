#include "spawn.hpp"
#include "../entities/enemies/factory.hpp"
#include "../environment.hpp"
#include "../../random.hpp"
#include "../../angle_vector.hpp"
#include "../../resolution.hpp"
#include <sge/math/constants.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <boost/tr1/random.hpp>
#include <algorithm>

void sanguis::server::waves::spawn(
	environment const &env,
	enemy_type::type const etype)
{
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
