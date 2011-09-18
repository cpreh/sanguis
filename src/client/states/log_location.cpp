#include <sanguis/client/states/log_location.hpp>
#include <sanguis/client/log_location.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/text.hpp>

fcppt::log::location const
sanguis::client::states::log_location()
{
	return
		client::log_location()
		/
		FCPPT_TEXT("states");
}