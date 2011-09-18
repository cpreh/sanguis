#include <sanguis/client/draw2d/sunlight/day_gradient.hpp>
#include <sanguis/client/draw2d/sunlight/gradients.hpp>
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
		grads.add(
			-3.14159f,
			color_point(
				(mizuiro::color::init::red %= 0.125736)
				(mizuiro::color::init::green %= 0.125736)
				(mizuiro::color::init::blue %= 0.219608)
			)
		);
		grads.add(
			-1.56924f,
			color_point(
				(mizuiro::color::init::red %= 0.125736)
				(mizuiro::color::init::green %= 0.125736)
				(mizuiro::color::init::blue %= 0.219608)
			)
		);
		grads.add(
			0,
			color_point(
				(mizuiro::color::init::red %= 0.125736)
				(mizuiro::color::init::green %= 0.125736)
				(mizuiro::color::init::blue %= 0.219608)
			)
		);
		grads.add(
			0.0916717f,
			color_point(
				(mizuiro::color::init::red %= 1.)
				(mizuiro::color::init::green %= 0.156863)
				(mizuiro::color::init::blue %= 0.156863)
			)
		);
		grads.add(
			0.153819f,
			color_point(
				(mizuiro::color::init::red %= 1.)
				(mizuiro::color::init::green %= 0.588235)
				(mizuiro::color::init::blue %= 0.)
			)
		);
		grads.add(
			0.785177f,
			color_point(
				(mizuiro::color::init::red %= 1.)
				(mizuiro::color::init::green %= 0.987313)
				(mizuiro::color::init::blue %= 0.90196)
			)
		);
		grads.add(
			2.37095f,
			color_point(
				(mizuiro::color::init::red %= 1.)
				(mizuiro::color::init::green %= 0.987313)
				(mizuiro::color::init::blue %= 0.90196)
			)
		);
		grads.add(
			2.95894f,
			color_point(
				(mizuiro::color::init::red %= 1.)
				(mizuiro::color::init::green %= 0.635294)
				(mizuiro::color::init::blue %= 0.)
			)
		);
		grads.add(
			3.0608f,
			color_point(
				(mizuiro::color::init::red %= 1.)
				(mizuiro::color::init::green %= 0.156863)
				(mizuiro::color::init::blue %= 0.156863)
			)
		);
		grads.add(
			3.14159f,
			color_point(
				(mizuiro::color::init::red %= 0.125736)
				(mizuiro::color::init::green %= 0.125736)
				(mizuiro::color::init::blue %= 0.219608)
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
