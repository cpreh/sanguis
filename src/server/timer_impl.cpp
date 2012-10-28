#include <sanguis/io_service.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/timer_duration.hpp>
#include <sanguis/server/timer_impl.hpp>
#include <alda/net/io_service_wrapper.hpp>
#include <fcppt/chrono/asio/expires_from_now_any.hpp>
#include <fcppt/tr1/functional.hpp>


sanguis::server::timer_impl::timer_impl(
	sanguis::io_service const &_io_service,
	sanguis::server::timer_callback const &_callback,
	sanguis::server::timer_duration const &_duration
)
:
	callback_(
		_callback
	),
	duration_(
		_duration
	),
	deadline_timer_(
		_io_service.impl().get()
	)
{
	this->reset();
}

sanguis::server::timer_impl::~timer_impl()
{
}

void
sanguis::server::timer_impl::handler()
{
	callback_();

	this->reset();
}

void
sanguis::server::timer_impl::reset()
{
	fcppt::chrono::asio::expires_from_now_any(
		deadline_timer_,
		duration_
	);

	deadline_timer_.async_wait(
		std::tr1::bind(
			&sanguis::server::timer_impl::handler,
			this
		)
	);
}
