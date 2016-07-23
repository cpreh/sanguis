#include <sanguis/app_name.hpp>
#include <sanguis/log_location.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/name.hpp>


fcppt::log::location
sanguis::log_location()
{
	return
		fcppt::log::location(
			fcppt::log::name{
				sanguis::app_name()
			}
		);
}
