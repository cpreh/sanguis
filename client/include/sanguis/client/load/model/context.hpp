#ifndef SANGUIS_CLIENT_LOAD_MODEL_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_CONTEXT_HPP_INCLUDED

#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
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
	sanguis::client::load::model::collection const &
	operator()() const;
private:
	friend class sanguis::client::load::context;

	explicit
	context(
		sanguis::client::load::resource::context const &
	);

	~context();

	mutable fcppt::scoped_ptr<
		sanguis::client::load::model::collection
	> collection_;
};

}
}
}
}

#endif
