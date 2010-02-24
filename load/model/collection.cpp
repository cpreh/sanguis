#include "collection.hpp"
#include "make_path.hpp"
#include "model.hpp"
#include <utility>

sanguis::load::model::model const &
sanguis::load::model::collection::operator[](
	fcppt::string const &name
) const
{
	model_map::const_iterator it(
		models.find(
			name
		)
	);

	if(
		it == models.end()
	)
		it = models.insert(
			std::make_pair(
				name,
				model(
					make_path(
						name
					),
					ctx
				)
			)
		).first;

	return it->second;	
}

sanguis::load::model::collection::collection(
	resource::context const &ctx
)
:
	ctx(ctx)
{}
