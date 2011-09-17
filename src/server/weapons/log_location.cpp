#include "log_location.hpp"
#include "../log_location.hpp"
#include <fcppt/log/location.hpp>
#include <fcppt/text.hpp>

fcppt::log::location const
sanguis::server::weapons::log_location()
{
	return
		server::log_location()
		/
		FCPPT_TEXT("weapons");
}
