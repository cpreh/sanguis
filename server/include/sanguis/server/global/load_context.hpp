#ifndef SANGUIS_SERVER_GLOBAL_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/load/model/path_fwd.hpp>
#include <sanguis/server/load_cref.hpp>
#include <sanguis/server/radius_fwd.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/global/next_id_callback.hpp>
#include <fcppt/nonmovable.hpp>


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
	FCPPT_NONMOVABLE(
		load_context
	);
public:
	load_context(
		sanguis::server::load_cref,
		sanguis::server::global::next_id_callback &&
	);

	~load_context()
	override;
private:
	[[nodiscard]]
	sanguis::server::radius
	model_size(
		sanguis::load::model::path const &
	) const
	override;

	[[nodiscard]]
	sanguis::entity_id
	next_id()
	override;

	sanguis::server::load_cref const model_context_;

	sanguis::server::global::next_id_callback const next_id_callback_;
};

}
}
}

#endif
