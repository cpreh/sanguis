#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/context.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


sanguis::client::load::model::collection const &
sanguis::client::load::model::context::operator()() const
{
	return
		*collection_;
}

sanguis::client::load::model::context::context(
	sanguis::client::load::resource::context const &_ctx
)
:
	collection_(
		fcppt::make_unique_ptr<
			sanguis::client::load::model::collection
		>(
			_ctx
		)
	)
{
}

sanguis::client::load::model::context::~context()
{
}
