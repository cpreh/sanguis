#include <sanguis/server/log_location.hpp>
#include <sanguis/server/weapons/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location const
sanguis::server::weapons::log_location()
{
	return
		sanguis::server::log_location()
		/
		FCPPT_TEXT("weapons");
}
