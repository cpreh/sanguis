#include <sanguis/log_parameters.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/log_location.hpp>
#include <fcppt/log/define_object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::client::log,
	sanguis::log_parameters(
		sanguis::client::log_location()
	)
)
