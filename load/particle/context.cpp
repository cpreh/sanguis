#include "context.hpp"
#include "../../media_path.hpp"

sanguis::load::particle::collection const &
sanguis::load::particle::context::operator()() const
{
	return col;
}

sanguis::load::particle::context::context(
	resource::context const &ctx)
:
	col(
		media_path(),
		ctx)
{}
