#ifndef SANGUIS_CLIENT_LOAD_MODEL_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_CONTEXT_HPP_INCLUDED

#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


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

	context(
		fcppt::log::context_reference,
		sanguis::client::load::resource::context const &
	);

	~context();

	fcppt::unique_ptr<
		sanguis::client::load::model::collection
	> const collection_;
};

}
}
}
}

#endif
