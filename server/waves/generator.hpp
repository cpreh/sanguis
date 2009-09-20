#ifndef SANGUIS_SERVER_WAVES_GENERATOR_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_GENERATOR_HPP_INCLUDED

#include "wave.hpp"
#include "../environment/object_ptr.hpp"
#include "../environment/load_context_ptr.hpp"
#include "../../time_type.hpp"
#include <sge/noncopyable.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{

namespace waves
{

class generator {
	SGE_NONCOPYABLE(generator)
public:
	generator();

	void
	process(
		time_type,
		environment::object_ptr,
		environment::load_context_ptr
	);
private:
	typedef boost::ptr_list<wave> wave_list;
	wave_list waves;
};

}
}
}

#endif
