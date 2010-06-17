#include "day_gradient.hpp"
#include "gradients.hpp"
#include <fcppt/math/pi.hpp>
#include <mizuiro/color/object.hpp>
#include <mizuiro/color/init/red.hpp>
#include <mizuiro/color/init/blue.hpp>
#include <mizuiro/color/init/green.hpp>

namespace
{
struct color
{
	sanguis::client::draw2d::sunlight::gradients grads;

	typedef sanguis::client::draw2d::sunlight::gradients::value color_point;

	color()
	{
		typedef sanguis::client::draw2d::sunlight::real real;

		real const pi(
			fcppt::math::pi<
				real
			>()
		);

		// TODO: nille!
		// TODO: add gradients for [-pi, pi]!
		grads.add(
			0,
			color_point(
				mizuiro::color::init::red %= 0.09,
				mizuiro::color::init::green %= 0.,
				mizuiro::color::init::blue %= 0.55
			)
		);

		grads.add(
			0.1f,
			color_point(
				mizuiro::color::init::red %= 1.0,
				mizuiro::color::init::green %= 0.67,
				mizuiro::color::init::blue %= 0.15
			)
		);

		grads.add(
			0.2f,
			color_point(
				mizuiro::color::init::red %= 1.0,
				mizuiro::color::init::green %= 1.0,
				mizuiro::color::init::blue %= 1.0
			)
		);

		grads.add(
			0.8f,
			color_point(
				mizuiro::color::init::red %= 1.0,
				mizuiro::color::init::green %= 1.0,
				mizuiro::color::init::blue %= 1.0
			)
		);

		grads.add(
			1.f,
			color_point(
				mizuiro::color::init::red %= 0.09,
				mizuiro::color::init::green %= 0.,
				mizuiro::color::init::blue %= 0.55
			)
		);
	}
} global;
	
}

sanguis::client::draw2d::sunlight::gradients const &
sanguis::client::draw2d::sunlight::day_gradient()
{
	return global.grads;
}
