#ifndef SANGUIS_WAVES_GENERATOR_HPP_INCLUDED
#define SANGUIS_WAVES_GENERATOR_HPP_INCLUDED

#include "wave.hpp"
#include "../../time_type.hpp"
#include "../../diff_clock.hpp"
#include <sge/time/timer.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{

struct environment;

namespace waves
{

class generator : boost::noncopyable {
public:
	generator();
	void process(
		time_type,
		environment const &);
private:
	diff_clock         diff_clock_;
	sge::time::timer   wave_timer;
	unsigned           wave_counter;
	typedef boost::ptr_list<wave> wave_list;
	wave_list waves;
};

}
}
}

#endif
