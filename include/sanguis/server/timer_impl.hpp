#ifndef SANGUIS_SERVER_TIMER_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_TIMER_IMPL_HPP_INCLUDED

#include <sanguis/io_service_fwd.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/timer_duration.hpp>
#include <sanguis/server/timer_impl_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/basic_waitable_timer.hpp>
#include <fcppt/config/external_end.hpp>


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

	typedef
	boost::asio::basic_waitable_timer<
		std::chrono::steady_clock
	>
	timer;

	timer deadline_timer_;
};

}
}

#endif
