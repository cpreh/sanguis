#ifndef SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/server/model_name_fwd.hpp>
#include <sanguis/server/model_size_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace environment
{

class load_context
{
	FCPPT_NONCOPYABLE(
		load_context
	);
protected:
	load_context();
public:
	virtual
	sanguis::server::model_size const
	model_size(
		sanguis::server::model_name const &
	) const = 0;

	virtual
	sanguis::entity_id const
	next_id() = 0;

	virtual
	~load_context() = 0;
};

}
}
}

#endif
