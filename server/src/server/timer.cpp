#include <sanguis/io_service_ref.hpp>
#include <sanguis/server/timer.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/timer_duration.hpp>
#include <sanguis/server/timer_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::timer::timer(
	sanguis::io_service_ref const _io_service,
	sanguis::server::timer_callback &&_callback,
	sanguis::server::timer_duration const &_duration
)
:
	impl_(
		fcppt::make_unique_ptr<
			sanguis::server::timer_impl
		>(
			_io_service,
			std::move(
				_callback
			),
			std::move(
				_duration
			)
		)
	)
{
}

sanguis::server::timer::~timer()
= default;
