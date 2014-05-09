#ifndef SANGUIS_SERVER_GLOBAL_LOAD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_LOAD_CONTEXT_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/server/load_fwd.hpp>
#include <sanguis/server/model_name_fwd.hpp>
#include <sanguis/server/model_size_fwd.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/global/next_id_callback.hpp>
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
	load_context(
		sanguis::server::load const &,
		sanguis::server::global::next_id_callback const &
	);

	~load_context()
	override;
private:
	sanguis::server::model_size const
	model_size(
		sanguis::server::model_name const &
	) const
	override;

	sanguis::entity_id const
	next_id()
	override;

	sanguis::server::load const &model_context_;

	sanguis::server::global::next_id_callback const next_id_callback_;
};

}
}
}

#endif
