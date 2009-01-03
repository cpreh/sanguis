#include "collection.hpp"
#include "../../media_path.hpp"
#include "../../exception.hpp"
#include <sge/filesystem/exists.hpp>
#include <utility>

sanguis::load::model::model const &
sanguis::load::model::collection::operator[](
	sge::string const &name) const
{
	model_map::const_iterator it(models.find(name));
	if(it == models.end())
	{
		sge::filesystem::path const path(
			media_path() / name);
		
		if(!sge::filesystem::exists(path))
			throw exception(
				SGE_TEXT("Model ")
				+ name
				+ SGE_TEXT(" not found!"));

		it = models.insert(
			std::make_pair(
				name,
				model(
					path,
					ctx))
			).first;
	}
	return it->second;	
}

sanguis::load::model::collection::collection(
	resource::context const &ctx)
:
	ctx(ctx)
{}
