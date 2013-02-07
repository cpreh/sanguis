#ifndef SANGUIS_SERVER_GLOBAL_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/load/server_context_fwd.hpp>
#include <sanguis/server/dim_fwd.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace global
{

class load_context
:
	public sanguis::server::environment::load_context
{
	FCPPT_NONCOPYABLE(
		load_context
	);
public:
	explicit
	load_context(
		sanguis::load::server_context const &
	);

	~load_context();
private:
	sanguis::server::dim const
	entity_dim(
		sanguis::server::string const &model_name
	) const;

	sanguis::load::server_context const &model_context_;
};

}
}
}

#endif
