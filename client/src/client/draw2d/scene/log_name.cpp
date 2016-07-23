#include <sanguis/client/draw2d/scene/log_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/name.hpp>


fcppt::log::name
sanguis::client::draw2d::scene::log_name()
{
	return
		fcppt::log::name{
			FCPPT_TEXT("scene")
		};
}
