#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::environment::insert_no_result(
	sanguis::server::environment::object &_environment,
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_parameters
)
{
	_environment.insert(
		std::move(
			_entity
		),
		_parameters
	);
}
