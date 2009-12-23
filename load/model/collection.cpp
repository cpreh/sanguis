#include "collection.hpp"
#include "../../media_path.hpp"
#include "../../exception.hpp"
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/text.hpp>
#include <utility>

sanguis::load::model::model const &
sanguis::load::model::collection::operator[](
	fcppt::string const &name) const
{
	model_map::const_iterator it(models.find(name));
	if(it == models.end())
	{
		fcppt::filesystem::path const path(
			media_path() / name);
		
		if(!fcppt::filesystem::exists(path))
			throw exception(
				FCPPT_TEXT("Model ")
				+ name
				+ FCPPT_TEXT(" not found!"));

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
