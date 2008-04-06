#include "model.hpp"
#include <sge/exception.hpp>
#include <utility>

sanguis::load::model::model::model(
	sge::path const& path)
{
	for(sge::directory_iterator beg(path), end; beg != end; ++beg)
		parts.insert(std::make_pair(beg->leaf(), part(*beg)));
}

sanguis::load::model::part const&
sanguis::load::model::model::operator[](sge::string const& name) const
{
	const part_map::const_iterator it(parts.find(name));
	if(it == parts.end())
		throw sge::exception(name + SGE_TEXT(" not found in model!"));
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
