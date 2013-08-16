#include <sanguis/load/model/collection.hpp>
#include <sanguis/load/model/context.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


sanguis::load::model::collection const &
sanguis::load::model::context::operator()() const
{
	return *collection_;
}

sanguis::load::model::context::context(
	sanguis::load::resource::context const &_ctx
)
:
	collection_(
		fcppt::make_unique_ptr<
			sanguis::load::model::collection
		>(
			_ctx
		)
	)
{
}

sanguis::load::model::context::~context()
{
}
