#include <sanguis/log_parameters.hpp>
#include <sanguis/tools/libmergeimage/log_location.hpp>
#include <sanguis/tools/libmergeimage/aux_/log.hpp>
#include <fcppt/log/define_object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::tools::libmergeimage::aux_::log,
	sanguis::log_parameters(
		sanguis::tools::libmergeimage::log_location()
	)
)
