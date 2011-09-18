#include <sanguis/server/states/log_location.hpp>
#include <sanguis/server/log_location.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/text.hpp>

fcppt::log::location const
sanguis::server::states::log_location()
{
	return
		server::log_location()
		/
		FCPPT_TEXT("states");
}
