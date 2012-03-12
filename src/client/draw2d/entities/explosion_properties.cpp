#include <sanguis/client/draw2d/entities/explosion_properties.hpp>
#include <sanguis/client/draw2d/particle/align_type.hpp>
#include <sanguis/client/draw2d/particle/anim_speed.hpp>
#include <sanguis/client/draw2d/particle/dispersion_range.hpp>
#include <sanguis/client/draw2d/particle/fade_range.hpp>
#include <sanguis/client/draw2d/particle/gen_frequency.hpp>
#include <sanguis/client/draw2d/particle/gen_life_time.hpp>
#include <sanguis/client/draw2d/particle/movement_type.hpp>
#include <sanguis/client/draw2d/particle/properties.hpp>
#include <sanguis/client/draw2d/particle/particle_type.hpp>
#include <sanguis/client/draw2d/particle/rot_speed_range.hpp>
#include <sanguis/client/draw2d/particle/spawn_initial.hpp>
#include <sanguis/client/draw2d/particle/speed_range.hpp>
#include <sanguis/duration_second.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/homogenous_pair_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

sanguis::client::draw2d::particle::property_container const prop_(
	fcppt::assign::make_container<
		sanguis::client::draw2d::particle::property_container
	>(
		std::make_pair(
			sanguis::client::draw2d::particle::particle_type::flare,
			sanguis::client::draw2d::particle::properties(
				sanguis::client::draw2d::particle::anim_speed(
					0.03f
				),
				sanguis::client::draw2d::particle::spawn_initial(
					5u
				),
				sanguis::client::draw2d::particle::gen_life_time(
					sanguis::duration_second(
						0
					)
				),
				sanguis::client::draw2d::particle::gen_frequency(
					sanguis::duration_second(
						0
					)
				),
				sanguis::client::draw2d::particle::align_type::random,
				sanguis::client::draw2d::particle::dispersion_range(
					sanguis::client::draw2d::particle::dispersion_range::value_type(
						0,
						50
					)
				),
				sanguis::client::draw2d::particle::speed_range(
					sanguis::client::draw2d::particle::speed_range::value_type(
						0,
						0
					)
				),
				sanguis::client::draw2d::particle::rot_speed_range(
					sanguis::client::draw2d::particle::rot_speed_range::value_type(
						0,
						10
					)
				),
				sanguis::client::draw2d::particle::fade(
					false
				),
				sanguis::client::draw2d::particle::fade_range(
					sanguis::client::draw2d::particle::fade_range::value_type(
						0,
						0
					)
				),
				sanguis::client::draw2d::particle::movement_type::random
			)
		)
	)
	(
		std::make_pair(
			sanguis::client::draw2d::particle::particle_type::smoke,
			sanguis::client::draw2d::particle::properties(
				sanguis::client::draw2d::particle::anim_speed(
					0.04f
				),
				sanguis::client::draw2d::particle::spawn_initial(
					9u
				),
				sanguis::client::draw2d::particle::gen_life_time(
					sanguis::duration_second(
						0
					)
				),
				sanguis::client::draw2d::particle::gen_frequency(
					sanguis::duration_second(
						0
					)
				),
				sanguis::client::draw2d::particle::align_type::to_center,
				sanguis::client::draw2d::particle::dispersion_range(
					sanguis::client::draw2d::particle::dispersion_range::value_type(
						0,
						20
					)
				),
				sanguis::client::draw2d::particle::speed_range(
					sanguis::client::draw2d::particle::speed_range::value_type(
						100,
						250
					)
				),
				sanguis::client::draw2d::particle::rot_speed_range(
					sanguis::client::draw2d::particle::rot_speed_range::value_type(
						0,
						0
					)
				),
				sanguis::client::draw2d::particle::fade(
					true
				),
				sanguis::client::draw2d::particle::fade_range(
					sanguis::client::draw2d::particle::fade_range::value_type(
						2,
						10
					)
				),
				sanguis::client::draw2d::particle::movement_type::expanding
			)
		)
	)
	(
		std::make_pair(
			sanguis::client::draw2d::particle::particle_type::rubble,
			sanguis::client::draw2d::particle::properties(
				sanguis::client::draw2d::particle::anim_speed(
					0.03f
				),
				sanguis::client::draw2d::particle::spawn_initial(
					0u
				),
				sanguis::client::draw2d::particle::gen_life_time(
					sanguis::duration_second(
						0
					)
				),
				sanguis::client::draw2d::particle::gen_frequency(
					sanguis::duration_second(
						0
					)
				),
				sanguis::client::draw2d::particle::align_type::random,
				sanguis::client::draw2d::particle::dispersion_range(
					sanguis::client::draw2d::particle::dispersion_range::value_type(
						0,
						40
					)
				),
				sanguis::client::draw2d::particle::speed_range(
					sanguis::client::draw2d::particle::speed_range::value_type(
						0,
						400
					)
				),
				sanguis::client::draw2d::particle::rot_speed_range(
					sanguis::client::draw2d::particle::rot_speed_range::value_type(
						0,
						10
					)
				),
				sanguis::client::draw2d::particle::fade(
					false
				),
				sanguis::client::draw2d::particle::fade_range(
					sanguis::client::draw2d::particle::fade_range::value_type(
						0,
						0
					)
				),
				sanguis::client::draw2d::particle::movement_type::random
			)
		)
	)
);

}

sanguis::client::draw2d::particle::property_container const &
sanguis::client::draw2d::entities::explosion_properties()
{
	return prop_;
}
