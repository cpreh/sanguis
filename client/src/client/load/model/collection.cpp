#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <sanguis/load/model/make_path.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/container/find_opt.hpp>


sanguis::client::load::model::object const &
sanguis::client::load::model::collection::operator[](
	fcppt::string const &_name
) const
{
	return
		*fcppt::from_optional(
			fcppt::container::find_opt(
				models_,
				_name
			),
			[
				this,
				&_name
			]()
			-> model_unique_ptr &
			{
				return
					models_.insert(
						std::make_pair(
							_name,
							fcppt::make_unique_ptr<
								sanguis::client::load::model::object
							>(
								sanguis::load::model::make_path(
									_name
								),
								ctx_
							)
						)
					).first->second;
			}
		);
}

sanguis::client::load::model::collection::collection(
	sanguis::client::load::resource::context const &_ctx
)
:
	ctx_(
		_ctx
	),
	models_()
{
}

sanguis::client::load::model::collection::~collection()
{
}
