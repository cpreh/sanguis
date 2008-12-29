#include "context.hpp"
#include "collection.hpp"
#include "../../media_path.hpp"
#include <sge/text.hpp>

sanguis::load::particle::collection const &
sanguis::load::particle::context::operator()() const
{
	if(!col)
		col.reset(
			new collection(
				media_path() / SGE_TEXT("particles"),
				ctx));
	return *col;
}

sanguis::load::particle::context::context(
	resource::context const &ctx)
:
	ctx(ctx)
{}

sanguis::load::particle::context::~context()
{}
