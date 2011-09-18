#ifndef SANGUIS_SERVER_GLOBAL_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/load/context_base.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace global
{

class load_context
:
	public environment::load_context
{
	FCPPT_NONCOPYABLE(
		load_context
	);
public:
	explicit load_context(
		load::context_base const &
	);

	~load_context();
private:
	server::dim const
	entity_dim(
		string const &model_name
	) const;

	load::context_base const &model_context_;
};

}
}
}

#endif
