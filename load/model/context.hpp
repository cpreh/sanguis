#ifndef SANGUIS_LOAD_MODEL_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONTEXT_HPP_INCLUDED

#include <sge/scoped_ptr.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace load
{

class context;

namespace resource
{
class context;
}
namespace model
{

class collection;

class context {
	SGE_NONCOPYABLE(context)
public:
	collection const &
	operator()() const;
private:
	friend class load::context;

	explicit context(
		resource::context const &);
	~context();

	resource::context const &ctx;

	mutable sge::scoped_ptr<
		collection
	> col;
};

}
}
}

#endif
