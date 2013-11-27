#include <sanguis/log_location.hpp>
#include <sanguis/net/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location
sanguis::net::log_location()
{
	return
		sanguis::log_location()
		/
		FCPPT_TEXT("net");
}
