#include <sanguis/log_parameters.hpp>
#include <sanguis/client/draw2d/log.hpp>
#include <sanguis/client/draw2d/log_location.hpp>
#include <fcppt/log/define_object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::client::draw2d::log,
	sanguis::log_parameters(
		sanguis::client::draw2d::log_location()
	)
)
