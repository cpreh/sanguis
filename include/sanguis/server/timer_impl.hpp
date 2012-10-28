#ifndef SANGUIS_SERVER_TIMER_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_TIMER_IMPL_HPP_INCLUDED

#include <sanguis/io_service_fwd.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/timer_duration.hpp>
#include <sanguis/server/timer_impl_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/chrono/asio/deadline_timer.hpp>


namespace sanguis
{
namespace server
{

class timer_impl
{
	FCPPT_NONCOPYABLE(
		timer_impl
	);
public:
	timer_impl(
		sanguis::io_service const &,
		sanguis::server::timer_callback const &,
		sanguis::server::timer_duration const &
	);

	~timer_impl();
private:
	void
	handler();

	void
	reset();

	sanguis::server::timer_callback const callback_;

	sanguis::server::timer_duration const duration_;

	fcppt::chrono::asio::deadline_timer deadline_timer_;
};

}
}

#endif
