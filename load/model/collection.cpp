#include "collection.hpp"
#include "make_path.hpp"
#include "object.hpp"
#include <utility>

sanguis::load::model::object const &
sanguis::load::model::collection::operator[](
	fcppt::string const &name
) const
{
	boost::mutex::scoped_lock const lock_(
		mutex_
	);

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
				object(
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
	ctx(ctx),
	models(),
	mutex_()
{}
