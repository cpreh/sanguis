#include "context.hpp"
#include "collection.hpp"

sanguis::load::model::collection const &
sanguis::load::model::context::operator()() const
{
	if(!col)
		col.reset(
			new collection(
				ctx));
	return *col;
}

sanguis::load::model::context::context(
	resource::context const &ctx)
:
	ctx(ctx)
{}

sanguis::load::model::context::~context()
{}
