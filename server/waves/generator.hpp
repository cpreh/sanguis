#ifndef SANGUIS_WAVES_GENERATOR_HPP_INCLUDED
#define SANGUIS_WAVES_GENERATOR_HPP_INCLUDED

#include "wave.hpp"
#include "../../time_type.hpp"
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
	typedef boost::ptr_list<wave> wave_list;
	wave_list waves;
};

}
}
}

#endif
