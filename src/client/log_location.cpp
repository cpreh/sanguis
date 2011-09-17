#include "log_location.hpp"
#include "../log_location.hpp"
#include <fcppt/log/location.hpp>
#include <fcppt/text.hpp>

fcppt::log::location const
sanguis::client::log_location()
{
	return
		sanguis::log_location()
		/
		FCPPT_TEXT("client");
}
