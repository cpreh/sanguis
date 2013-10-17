#include <sanguis/client/draw2d/sunlight/day_gradient.hpp>
#include <sanguis/client/draw2d/sunlight/gradients.hpp>
#include <sge/image/mizuiro_color.hpp>
#include <fcppt/noncopyable.hpp>
#include <mizuiro/color/object.hpp>
#include <mizuiro/color/init/red.hpp>
#include <mizuiro/color/init/blue.hpp>
#include <mizuiro/color/init/green.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

class color
{
	FCPPT_NONCOPYABLE(
		color
	);
public:
	sanguis::client::draw2d::sunlight::gradients const grads_;

	typedef sanguis::client::draw2d::sunlight::gradients::value color_point;

	color()
	:
		grads_{
			std::make_pair(
				-3.14159f,
				color_point(
					(mizuiro::color::init::red() %= 1.0)
					(mizuiro::color::init::green() %= 1.0)
					(mizuiro::color::init::blue() %= 1.0)
				)
			),
			std::make_pair(
				3.14159f,
				color_point(
					(mizuiro::color::init::red() %= 1.0)
					(mizuiro::color::init::green() %= 1.0)
					(mizuiro::color::init::blue() %= 1.0)
				)
			)
		}
	{
	}

	~color()
	{
	}
} global;

}

sanguis::client::draw2d::sunlight::gradients const &
sanguis::client::draw2d::sunlight::day_gradient()
{
	return global.grads_;
}
