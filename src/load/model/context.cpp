#include "context.hpp"
#include "collection.hpp"

sanguis::load::model::collection const &
sanguis::load::model::context::operator()() const
{
	return *collection_;
}

sanguis::load::model::context::context(
	resource::context const &ctx
)
:
	collection_(
		new collection(
			ctx
		)
	)
{}

sanguis::load::model::context::~context()
{}
