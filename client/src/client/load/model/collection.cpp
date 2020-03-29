#include <sanguis/log_parameters.hpp>
#include <sanguis/client/load/log_location.hpp>
#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sanguis/client/load/resource/context_fwd.hpp>
#include <sanguis/load/model/make_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>


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
					fcppt::make_unique_ptr<
						sanguis::client::load::model::object
					>(
						log_,
						sanguis::load::model::make_path(
							_npath
						),
						resources_
					);
			}
		);
}

sanguis::client::load::model::collection::collection(
	fcppt::log::context_reference const _log_context,
	sanguis::client::load::resource::context const &_resources
)
:
	log_{
		_log_context,
		sanguis::client::load::log_location(),
		sanguis::log_parameters(
			fcppt::log::name{
				FCPPT_TEXT("model")
			}
		)
	},
	resources_(
		_resources
	),
	models_()
{
}

sanguis::client::load::model::collection::~collection()
{
}
