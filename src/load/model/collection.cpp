#include <sanguis/load/model/collection.hpp>
#include <sanguis/load/model/make_path.hpp>
#include <sanguis/load/model/object.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>


sanguis::load::model::object const &
sanguis::load::model::collection::operator[](
	fcppt::string const &_name
) const
{
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
					sanguis::load::model::object
				>(
					sanguis::load::model::make_path(
						_name
					),
					ctx_
				)
			).first;

	return *it->second;
}

sanguis::load::model::collection::collection(
	sanguis::load::resource::context const &_ctx
)
:
	ctx_(
		_ctx
	),
	models_()
{
}

sanguis::load::model::collection::~collection()
{
}
