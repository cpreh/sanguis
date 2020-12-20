#include <sanguis/io_service.hpp>
#include <sanguis/io_service_ref.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/timer_duration.hpp>
#include <sanguis/server/timer_impl.hpp>
#include <alda/net/io_service_wrapper.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/system/error_code.hpp>
#include <chrono>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::timer_impl::timer_impl(
	sanguis::io_service_ref const _io_service,
	sanguis::server::timer_callback &&_callback,
	sanguis::server::timer_duration const &_duration
)
:
	callback_(
		std::move(
			_callback
		)
	),
	duration_(
		_duration
	),
	deadline_timer_(
		_io_service->impl().get()
	)
{
	this->reset();
}

sanguis::server::timer_impl::~timer_impl()
= default;

void
sanguis::server::timer_impl::handler()
{
	callback_();

	this->reset();
}

void
sanguis::server::timer_impl::reset()
{
	deadline_timer_.expires_from_now(
		std::chrono::duration_cast<
			timer::duration
		>(
			duration_
		)
	);

	deadline_timer_.async_wait(
		[
			this
		](
			boost::system::error_code const &_error
		){
			this->handler();
		}
	);
}
