#ifndef SANGUIS_CLIENT_DAYTIME_SETTINGS_HPP_INCLUDED
#define SANGUIS_CLIENT_DAYTIME_SETTINGS_HPP_INCLUDED

#include <sge/console/gfx_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <ctime>

namespace sanguis
{
namespace client
{

class daytime_settings
{
	FCPPT_NONCOPYABLE(daytime_settings)
public:
	explicit
	daytime_settings(
		sge::console::gfx &
	);

	std::tm const
	current_time();
private:
	void
	change_day(
		sge::console::arg_list const &
	);

	void
	change_time(
		sge::console::arg_list const &
	);

	void
	change_time_speed(
		sge::console::arg_list const &
	);

	void
	reset_day(
		sge::console::arg_list const &
	);

	void
	reset_time(
		sge::console::arg_list const &
	);

	void
	reset_time_speed(
		sge::console::arg_list const &
	);

	sge::console::gfx &console_;

	std::time_t time_begin_;

	std::time_t speedup_;

	fcppt::signal::scoped_connection const
		day_con_,
		time_con_,
		time_speed_con_,
		reset_day_con_,
		reset_time_con_;
	
	std::tm current_time_;
};

}
}

#endif
