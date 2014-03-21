#include <sanguis/log_parameters.hpp>
#include <sanguis/creator/log_location.hpp>
#include <sanguis/creator/aux_/log.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/parameters/object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::creator::aux_::log,
	sanguis::log_parameters(
		sanguis::creator::log_location()
	)
)
