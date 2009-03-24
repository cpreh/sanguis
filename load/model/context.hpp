#ifndef SANGUIS_LOAD_MODEL_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONTEXT_HPP_INCLUDED

#include "../context_fwd.hpp"
#include "../resource/context_fwd.hpp"
#include "collection_fwd.hpp"
#include <sge/scoped_ptr.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

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
