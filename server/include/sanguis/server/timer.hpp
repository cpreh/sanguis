#ifndef SANGUIS_SERVER_TIMER_HPP_INCLUDED
#define SANGUIS_SERVER_TIMER_HPP_INCLUDED

#include <sanguis/io_service_ref.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/timer_duration.hpp>
#include <sanguis/server/timer_fwd.hpp>
#include <sanguis/server/timer_impl_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::server
{

class timer
{
	FCPPT_NONMOVABLE(
		timer
	);
public:
	timer(
		sanguis::io_service_ref,
		sanguis::server::timer_callback &&,
		sanguis::server::timer_duration const &
	);

	~timer();
private:
	fcppt::unique_ptr<
		sanguis::server::timer_impl
	> const impl_;
};

}

#endif
