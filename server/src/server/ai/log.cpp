#include <sanguis/log_parameters.hpp>
#include <sanguis/server/ai/log.hpp>
#include <sanguis/server/ai/log_location.hpp>
#include <fcppt/log/define_object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::server::ai::log,
	sanguis::log_parameters(
		sanguis::server::ai::log_location()
	)
)
