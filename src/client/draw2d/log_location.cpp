#include <sanguis/client/log_location.hpp>
#include <sanguis/client/draw2d/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location const
sanguis::client::draw2d::log_location()
{
	return
		sanguis::client::log_location()
		/
		FCPPT_TEXT("draw2d");
}
