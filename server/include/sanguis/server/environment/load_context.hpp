#ifndef SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/load/model/path_fwd.hpp>
#include <sanguis/server/radius_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace environment
{

class load_context
{
	FCPPT_NONMOVABLE(
		load_context
	);
protected:
	load_context();
public:
	[[nodiscard]]
	virtual
	sanguis::server::radius
	model_size(
		sanguis::load::model::path const &
	) const = 0;

	[[nodiscard]]
	virtual
	sanguis::entity_id
	next_id() = 0;

	virtual
	~load_context();
};

}
}
}

#endif
