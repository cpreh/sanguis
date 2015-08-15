#include <sanguis/log_parameters.hpp>
#include <sanguis/client/log_location.hpp>
#include <sanguis/client/load/log.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/define_object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::client::load::log,
	sanguis::log_parameters(
		sanguis::client::log_location()
		/
		FCPPT_TEXT("load")
	)
)
