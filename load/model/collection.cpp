#include "collection.hpp"
#include "make_path.hpp"
#include "object.hpp"
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/make_unique_ptr.hpp>

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
		it =
			fcppt::container::ptr::insert_unique_ptr_map(
				models,
				name,
				fcppt::make_unique_ptr<
					object
				>(
					make_path(
						name
					),
					ctx
				)
			).first;

	return *it->second;	
}

sanguis::load::model::collection::~collection()
{
}

sanguis::load::model::collection::collection(
	resource::context const &ctx
)
:
	ctx(ctx),
	models(),
	mutex_()
{}
