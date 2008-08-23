#ifndef SANGUIS_SERVER_WAVES_WAVE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_WAVE_HPP_INCLUDED

#include "../../time_type.hpp"
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace server
{

struct environment;

namespace waves
{

class wave : boost::noncopyable {
public:
	virtual void process(
		time_type diff,
		environment const &) = 0;
	virtual ~wave();
};

}
}
}

#endif
