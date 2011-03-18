#include "explosion_properties.hpp"
#include "../particle/align_type.hpp"
#include "../particle/movement_type.hpp"
#include "../particle/properties.hpp"
#include "../particle/particle_type.hpp"
#include "../funit.hpp"
#include <fcppt/minmax_pair_impl.hpp>
#include <boost/assign/list_of.hpp>

namespace
{

sanguis::client::draw2d::particle::property_container const prop_ = boost::assign::map_list_of
(
	sanguis::client::draw2d::particle::particle_type::flare,
	sanguis::client::draw2d::particle::properties(
		static_cast<
			sanguis::client::draw2d::funit
		>(
			0.03
		),
		5,
		0,
		0,
		sanguis::client::draw2d::particle::align_type::random,
		sanguis::client::draw2d::particle::properties::dispersion_range(
			0,
			50
		),
		sanguis::client::draw2d::particle::properties::speed_range(
			0,
			0
		),
		sanguis::client::draw2d::particle::properties::rot_speed_range(
			0,
			10
		),
		false,
		sanguis::client::draw2d::particle::properties::fade_range(
			0,
			0
		),
		sanguis::client::draw2d::particle::movement_type::random
	)
)
(
	sanguis::client::draw2d::particle::particle_type::smoke,
	sanguis::client::draw2d::particle::properties(
		static_cast<
			sanguis::client::draw2d::funit
		>(
			0.04
		),
		9,
		0,
		0,
		sanguis::client::draw2d::particle::align_type::to_center,
		sanguis::client::draw2d::particle::properties::dispersion_range(
			0,
			20
		),
		sanguis::client::draw2d::particle::properties::speed_range(
			100,
			250
		),
		sanguis::client::draw2d::particle::properties::rot_speed_range(
			0,
			0
		),
		true,
		sanguis::client::draw2d::particle::properties::fade_range(
			2,
			10
		),
		sanguis::client::draw2d::particle::movement_type::expanding
	)
)
(
	sanguis::client::draw2d::particle::particle_type::rubble,
	sanguis::client::draw2d::particle::properties(
		static_cast<
			sanguis::client::draw2d::funit
		>(
			0.03
		),
		0,
		0,
		0,
		sanguis::client::draw2d::particle::align_type::random,
		sanguis::client::draw2d::particle::properties::dispersion_range(
			0,
			40
		),
		sanguis::client::draw2d::particle::properties::speed_range(
			0,
			400
		),
		sanguis::client::draw2d::particle::properties::rot_speed_range(
			0,
			10
		),
		false,
		sanguis::client::draw2d::particle::properties::fade_range(
			0,
			0
		),
		sanguis::client::draw2d::particle::movement_type::random
	)
)
;

}

sanguis::client::draw2d::particle::property_container const &
sanguis::client::draw2d::entities::explosion_properties()
{
	return prop_;
}
