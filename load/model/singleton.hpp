#ifndef SANGUIS_LOAD_MODEL_SINGLETON_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_SINGLETON_HPP_INCLUDED

#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class collection;

collection const& singleton();

struct connection : boost::noncopyable {
	connection();
	~connection();
};

}
}
}

#endif
