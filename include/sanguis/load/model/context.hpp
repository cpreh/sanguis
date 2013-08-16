#ifndef SANGUIS_LOAD_MODEL_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_CONTEXT_HPP_INCLUDED

#include <sanguis/load/context_fwd.hpp>
#include <sanguis/load/model/collection_fwd.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
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
	sanguis::load::model::collection const &
	operator()() const;
private:
	friend class sanguis::load::context;

	explicit
	context(
		sanguis::load::resource::context const &
	);

	~context();

	mutable fcppt::scoped_ptr<
		sanguis::load::model::collection
	> collection_;
};

}
}
}

#endif
