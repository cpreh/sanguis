#include "collection.hpp"
#include "../../media_path.hpp"
#include <sge/exception.hpp>
#include <utility>

sanguis::load::model::model const&
sanguis::load::model::collection::operator[](
	sge::string const& name) const
{
	model_map::const_iterator it(models.find(name));
	if(it == models.end())
	{
		const sge::path path(media_path() / name);
		if(!boost::filesystem::exists(path))
			throw sge::exception(SGE_TEXT("Model ") + name + SGE_TEXT(" not found!"));
		models.insert(
			std::make_pair(
				name,
				model(path))); // FIXME: why can't we assign the return value of insert to it?
		it = models.find(name);
	}
	return it->second;	
}

sanguis::load::model::collection::collection()
{}
