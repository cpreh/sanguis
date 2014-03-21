#include <sanguis/app_name.hpp>
#include <sanguis/log_location.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location
sanguis::log_location()
{
	return
		fcppt::log::location(
			sanguis::app_name()
		);
}
