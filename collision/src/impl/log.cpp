#include <sanguis/log_parameters.hpp>
#include <sanguis/collision/log_location.hpp>
#include <sanguis/collision/impl/log.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/location.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::collision::impl::log,
	sanguis::log_parameters(
		sanguis::collision::log_location()
	)
)
