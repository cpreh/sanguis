#include <sanguis/io_service_fwd.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/timer_duration.hpp>
#include <sanguis/server/timer.hpp>
#include <sanguis/server/timer_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::timer::timer(
	sanguis::io_service const &_io_service,
	sanguis::server::timer_callback const &_callback,
	sanguis::server::timer_duration const &_duration
)
:
	impl_(
		fcppt::make_unique_ptr<
			sanguis::server::timer_impl
		>(
			_io_service,
			_callback,
			_duration
		)
	)
{
}

sanguis::server::timer::~timer()
{
}
