#include "context.hpp"
#include "collection.hpp"
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::load::model::collection const &
sanguis::load::model::context::operator()() const
{
	return *collection_;
}

sanguis::load::model::context::context(
	resource::context const &_ctx
)
:
	collection_(
		fcppt::make_unique_ptr<
			model::collection
		>(
			fcppt::cref(
				_ctx
			)
		)
	)
{
}

sanguis::load::model::context::~context()
{
}
