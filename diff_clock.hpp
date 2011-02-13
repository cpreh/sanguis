#ifndef SANGUIS_DIFF_CLOCK_HPP_INCLUDED
#define SANGUIS_DIFF_CLOCK_HPP_INCLUDED

#include "time_type.hpp"
#include <sge/time/unit.hpp>
#include <sge/time/callback.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{

class diff_clock
{
	FCPPT_NONCOPYABLE(
		diff_clock
	);
public:
	diff_clock();

	void
	update(
		time_type
	);
	
	typedef sge::time::callback fun_type;

	fun_type const callback() const;
private:
	sge::time::unit time() const;

	sge::time::unit diff_time;
};


}

#endif
