#include "context.hpp"
#include "collection.hpp"

sanguis::load::model::collection const &
sanguis::load::model::context::operator()() const
{
	if(!col)
		col.reset(
			new collection());
	return *col;
}

sanguis::load::model::context::context()
{}

sanguis::load::model::context::~context()
{}
