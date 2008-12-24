#ifndef SANGUIS_LOAD_PARTICLE_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLE_CONTEXT_HPP_INCLUDED

#include "collection.hpp"
#include <sge/path.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace load
{

class context;

namespace resource
{
class context;
}
namespace particle
{

class context : boost::noncopyable {
public:
	collection const &
	operator()() const;
private:
	explicit context(
		resource::context const &);

	friend class load::context;

	collection col;
};

}
}
}

#endif
