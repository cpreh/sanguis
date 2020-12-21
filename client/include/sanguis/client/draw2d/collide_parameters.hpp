#ifndef SANGUIS_CLIENT_DRAW2D_COLLIDE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_COLLIDE_PARAMETERS_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/collide_parameters_fwd.hpp>
#include <sanguis/client/draw2d/fradius.hpp>
#include <sanguis/client/draw2d/speed.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{

class collide_parameters
{
public:
	collide_parameters(
		sanguis::duration,
		sanguis::client::draw2d::center,
		sanguis::client::draw2d::speed,
		sanguis::client::draw2d::fradius
	);

	[[nodiscard]]
	sanguis::duration
	duration() const;

	[[nodiscard]]
	sanguis::client::draw2d::center
	center() const;

	[[nodiscard]]
	sanguis::client::draw2d::speed
	speed() const;

	[[nodiscard]]
	sanguis::client::draw2d::fradius
	radius() const;
private:
	sanguis::duration duration_;

	sanguis::client::draw2d::center center_;

	sanguis::client::draw2d::speed speed_;

	sanguis::client::draw2d::fradius radius_;
};

}
}
}

#endif
