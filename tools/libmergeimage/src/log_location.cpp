#include <sanguis/log_location.hpp>
#include <sanguis/tools/libmergeimage/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location
sanguis::tools::libmergeimage::log_location()
{
	return
		sanguis::log_location()
		/
		FCPPT_TEXT("libmergeimage");
}
