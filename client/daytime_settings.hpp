#ifndef SANGUIS_CLIENT_DAYTIME_SETTINGS_HPP_INCLUDED
#define SANGUIS_CLIENT_DAYTIME_SETTINGS_HPP_INCLUDED

#include "daytime_settings_fwd.hpp"
#include <sge/console/object_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/chrono/system_clock.hpp>
#include <fcppt/chrono/time_point_decl.hpp>
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
		sge::console::object &
	);

	~daytime_settings();

	std::tm const
	current_time();
private:
	typedef fcppt::chrono::system_clock clock;

	typedef clock::time_point time_point;

	typedef time_point::rep time_rep;

	void
	change_day(
		sge::console::arg_list const &,
		sge::console::object &
	);

	void
	change_time(
		sge::console::arg_list const &,
		sge::console::object &
	);

	void
	change_time_speed(
		sge::console::arg_list const &,
		sge::console::object &
	);

	void
	reset_day(
		sge::console::arg_list const &,
		sge::console::object &
	);

	void
	reset_time(
		sge::console::arg_list const &,
		sge::console::object &
	);

	void
	reset_time_speed(
		sge::console::arg_list const &,
		sge::console::object &
	);

	static time_point const
	now();

	time_point time_begin_;

	time_rep speedup_;

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
