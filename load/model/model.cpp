#include "model.hpp"
#include "../../exception.hpp"
#include "../log.hpp"
#include <sge/text.hpp>
#include <sge/log/headers.hpp>
#include <boost/filesystem/convenience.hpp>
#include <ostream>
#include <utility>

sanguis::load::model::model::model(
	sge::path const &path,
	resource::context const &ctx)
{
	for(sge::directory_iterator beg(path), end; beg != end; ++beg)
	{
		if(!boost::filesystem::is_directory(*beg))
		{
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< *beg
					<< SGE_TEXT(" is not a directory!"));
			continue;
		}
		
		if(parts.insert(
			std::make_pair(
				boost::filesystem::basename(*beg),
				part(
					*beg,
					ctx)))
		.second == false)
			throw exception(
				SGE_TEXT("Double insert in model::model: ")
				+ beg->string());
	}
}

sanguis::load::model::part const &
sanguis::load::model::model::operator[](
	sge::string const &name) const
{
	part_map::const_iterator const it(parts.find(name));
	if(it == parts.end())
		throw exception(name + SGE_TEXT(" not found in model!"));
	return it->second;
}

sanguis::load::model::model::const_iterator
sanguis::load::model::model::begin() const
{
	return parts.begin();
}

sanguis::load::model::model::const_iterator
sanguis::load::model::model::end() const
{
	return parts.end();
} 
sanguis::load::model::model::size_type
sanguis::load::model::model::size() const
{
	return parts.size();
}
