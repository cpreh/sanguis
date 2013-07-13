#ifndef SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/server/dim_fwd.hpp>
#include <sanguis/server/model_name.hpp>
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
	sanguis::server::dim const
	entity_dim(
		sanguis::server::model_name const &
	) const = 0;

	// TODO: Should this be const?
	virtual
	sanguis::entity_id const
	next_id() const = 0;

	virtual
	~load_context();
};

}
}
}

#endif
