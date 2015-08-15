#include <sanguis/log_parameters.hpp>
#include <sanguis/tiles/log_location.hpp>
#include <sanguis/tiles/impl/log.hpp>
#include <fcppt/log/define_object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::tiles::impl::log,
	sanguis::log_parameters(
		sanguis::tiles::log_location()
	)
)
