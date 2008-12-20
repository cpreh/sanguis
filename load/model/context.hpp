#ifndef SANGUIS_LOAD_MODEL_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONTEXT_HPP_INCLUDED

#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace load
{

class context;

namespace model
{

class collection;

class context : boost::noncopyable {
public:
	collection const &
	operator()() const;
private:
	friend class load::context;

	context();
	~context();

	mutable boost::scoped_ptr<
		collection
	> col;
};

}
}
}

#endif
