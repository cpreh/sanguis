#ifndef SANGUIS_SERVER_TIMER_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_TIMER_IMPL_HPP_INCLUDED

#include <sanguis/io_service_ref.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/timer_duration.hpp>
#include <sanguis/server/timer_impl_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/basic_waitable_timer.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server
{

class timer_impl
{
  FCPPT_NONMOVABLE(timer_impl);

public:
  timer_impl(
      sanguis::io_service_ref,
      sanguis::server::timer_callback &&,
      sanguis::server::timer_duration const &);

  ~timer_impl();

private:
  void handler();

  void reset();

  sanguis::server::timer_callback const callback_;

  sanguis::server::timer_duration const duration_;

  using timer = boost::asio::basic_waitable_timer<std::chrono::steady_clock>;

  timer deadline_timer_;
};

}

#endif
