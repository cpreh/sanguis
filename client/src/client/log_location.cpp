#include <sanguis/log_location.hpp>
#include <sanguis/client/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location
sanguis::client::log_location()
{
	return
		sanguis::log_location()
		/
		FCPPT_TEXT("client");
}
