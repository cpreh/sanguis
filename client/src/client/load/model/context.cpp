#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/context.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/context_reference.hpp>


sanguis::client::load::model::collection const &
sanguis::client::load::model::context::operator()() const
{
	return
		*collection_;
}

sanguis::client::load::model::context::context(
	fcppt::log::context_reference const _log_context,
	sanguis::client::load::resource::context const &_context
)
:
	collection_(
		fcppt::make_unique_ptr<
			sanguis::client::load::model::collection
		>(
			_log_context,
			_context
		)
	)
{
}

sanguis::client::load::model::context::~context()
{
}
