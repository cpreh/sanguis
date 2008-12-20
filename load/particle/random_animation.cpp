#include "random_animation.hpp"
#include "animation.hpp"
#include "../../media_path.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/string.hpp>

namespace
{

sge::string const
to_name(
	sanguis::particle_type::type);

}

sanguis::load::particle::animation const
sanguis::load::particle::random_animation(
	particle_type::type const pt)
{
	sge::path const p(
		media_path() / to_name(pt));
	
}

namespace
{

sge::string const
to_name(
	sanguis::particle_type::type const pt)
{
	switch(pt) {
	case sanguis::particle_type::flare:
		return SGE_TEXT("flare");
	case sanguis::particle_type::smoke:
		return SGE_TEXT("smoke");
	case sanguis::particle_type::rubble:
		return SGE_TEXT("rubble");
	default:
		throw sge::exception(
			SGE_TEXT("Invalid particle_type!"));
	}
}

}
