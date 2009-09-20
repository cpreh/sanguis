#ifndef SANGUIS_SERVER_WORLD_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_LOAD_CONTEXT_HPP_INCLUDED

#include "../environment/load_context.hpp"
#include "../dim_type.hpp"
#include "../string.hpp"
#include "../../load/model/context_fwd.hpp"

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
public:
	explicit load_context(
		load::model::context const &
	);
private:
	dim_type const
	entity_dim(
		string const &model_name
	) const;
	
	load::model::context const &model_context_;
};

}
}
}

#endif
