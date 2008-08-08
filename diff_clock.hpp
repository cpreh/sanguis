#ifndef SANGUIS_DIFF_CLOCK_HPP_INCLUDED
#define SANGUIS_DIFF_CLOCK_HPP_INCLUDED

#include "time_type.hpp"
#include <sge/time/types.hpp>
#include <sge/time/fun.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{

class diff_clock : boost::noncopyable {
public:
	diff_clock();

	void update(
		time_type);
	
	typedef sge::time::fun fun_type;

	fun_type const callback() const;
private:
	sge::time::unit time() const;

	sge::time::unit diff_time;
};


}

#endif
