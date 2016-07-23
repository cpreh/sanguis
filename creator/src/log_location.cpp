#include <sanguis/log_location.hpp>
#include <sanguis/creator/log_location.hpp>
#include <sanguis/creator/impl/log_name.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location
sanguis::creator::log_location()
{
	return
		sanguis::log_location()
		/
		sanguis::creator::impl::log_name();
}
