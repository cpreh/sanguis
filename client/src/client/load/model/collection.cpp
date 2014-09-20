#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <sanguis/load/model/make_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/find_opt.hpp>


sanguis::client::load::model::object const &
sanguis::client::load::model::collection::operator[](
	sanguis::load::model::path const &_path
) const
{
	return
		*fcppt::from_optional(
			fcppt::container::find_opt(
				models_,
				_path
			),
			[
				this,
				&_path
			]()
			-> model_unique_ptr &
			{
				return
					models_.insert(
						std::make_pair(
							_path,
							fcppt::make_unique_ptr<
								sanguis::client::load::model::object
							>(
								sanguis::load::model::make_path(
									_path
								),
								resources_
							)
						)
					).first->second;
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
