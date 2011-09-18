#ifndef SANGUIS_LOAD_MODEL_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONTEXT_HPP_INCLUDED

#include <sanguis/load/model/collection_fwd.hpp>
#include <sanguis/load/context_fwd.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	collection const &
	operator()() const;
private:
	friend class load::context;

	explicit context(
		resource::context const &
	);

	~context();

	mutable fcppt::scoped_ptr<
		collection
	> collection_;
};

}
}
}

#endif
