#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <sanguis/load/model/make_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/container/get_or_insert.hpp>


sanguis::client::load::model::object const &
sanguis::client::load::model::collection::operator[](
	sanguis::load::model::path const &_path
) const
{
	return
		*fcppt::container::get_or_insert(
			models_,
			_path,
			[
				this
			](
				sanguis::load::model::path const &_npath
			)
			{
				return
					fcppt::make_unique_ptr_fcppt<
						sanguis::client::load::model::object
					>(
						sanguis::load::model::make_path(
							_npath
						),
						resources_
					);
			}
		);
}

sanguis::client::load::model::collection::collection(
	sanguis::client::load::resource::context const &_resources
)
:
	resources_(
		_resources
	),
	models_()
{
}

sanguis::client::load::model::collection::~collection()
{
}
