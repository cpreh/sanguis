#include "collection.hpp"
#include "make_path.hpp"
#include "object.hpp"
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::load::model::object const &
sanguis::load::model::collection::operator[](
	fcppt::string const &_name
) const
{
	boost::mutex::scoped_lock const lock(
		mutex_
	);

	model_map::const_iterator it(
		models_.find(
			_name
		)
	);

	if(
		it == models_.end()
	)
		it =
			fcppt::container::ptr::insert_unique_ptr_map(
				models_,
				_name,
				fcppt::make_unique_ptr<
					object
				>(
					model::make_path(
						_name
					),
					ctx_
				)
			).first;

	return *it->second;	
}

sanguis::load::model::collection::~collection()
{
}

sanguis::load::model::collection::collection(
	resource::context const &_ctx
)
:
	ctx_(_ctx),
	models_(),
	mutex_()
{}
