#include <sanguis/server/log_location.hpp>
#include <sanguis/server/states/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location
sanguis::server::states::log_location()
{
	return
		sanguis::server::log_location()
		/
		FCPPT_TEXT("states");
}
