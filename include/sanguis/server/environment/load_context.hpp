#ifndef SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/server/dim_fwd.hpp>
#include <sanguis/server/string.hpp>
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
		sanguis::server::string const &model_name
	) const = 0;

	virtual
	~load_context();
};

}
}
}

#endif
