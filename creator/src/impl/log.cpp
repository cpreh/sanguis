#include <sanguis/log_parameters.hpp>
#include <sanguis/creator/log_location.hpp>
#include <sanguis/creator/impl/log.hpp>
#include <fcppt/log/define_object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::creator::impl::log,
	sanguis::log_parameters(
		sanguis::creator::log_location()
	)
)
