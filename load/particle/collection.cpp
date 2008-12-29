#include "collection.hpp"
#include "animations.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <sge/auto_ptr.hpp>
#include <sge/make_auto_ptr.hpp>
#include <boost/filesystem/convenience.hpp>

namespace
{

sanguis::particle_type::type
from_name(
	sge::string const &);

}

sanguis::load::particle::animations const &
sanguis::load::particle::collection::operator[](
	particle_type::type const pt) const
{
	animations_map::const_iterator const it(
		animations_.find(
			pt));
	if(it == animations_.end())
		throw exception(
			SGE_TEXT("Animations not found in particle!"));
	return *it->second;
}

sanguis::load::particle::collection::collection(
	sge::path const &p,
	resource::context const &ctx)
{
	for(
		sge::directory_iterator it(p), end;
		it != end;
		++it)
	{
		if(!boost::filesystem::is_directory(*it))
		{
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< *it
					<< SGE_TEXT(" is not a directory!"));
			continue;
		}

		sge::auto_ptr<
			animations
		> anim(
			sge::make_auto_ptr<
				animations
			>(
				*it,
				ctx));
		
		animations_.insert(
			from_name(
				boost::filesystem::basename(
					*it)),
			anim);
	}
}

sanguis::load::particle::collection::~collection()
{}

namespace
{

sanguis::particle_type::type
from_name(
	sge::string const &str)
{
	if(str == SGE_TEXT("flare"))
		return sanguis::particle_type::flare;
	if(str == SGE_TEXT("smoke"))
		return sanguis::particle_type::smoke;
	if(str == SGE_TEXT("rubble"))
		return sanguis::particle_type::rubble;
	throw sanguis::exception(
		SGE_TEXT("Invalid particle directory: ") + str);
}

}
