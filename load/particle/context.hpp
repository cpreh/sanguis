#ifndef SANGUIS_LOAD_PARTICLE_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_PARTICLE_CONTEXT_HPP_INCLUDED

#include "../context_fwd.hpp"
#include "../resource/context_fwd.hpp"
#include <sge/scoped_ptr.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace particle
{

class collection;

class context {
	SGE_NONCOPYABLE(context)
public:
	collection const &
	operator()() const;
private:
	explicit context(
		resource::context const &);
	~context();

	void preload() const;

	friend class load::context;

	resource::context const &ctx;

	mutable sge::scoped_ptr<
		collection
	> col;
};

}
}
}

#endif
