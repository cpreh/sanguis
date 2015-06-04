#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/entities/simple.hpp>
#include <sanguis/server/entities/simple_unique_ptr.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/cast/to_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	typename Entity
>
void
insert_no_result_impl(
	sanguis::server::environment::object &_environment,
	fcppt::unique_ptr<
		Entity
	> &&_entity,
	sanguis::server::entities::insert_parameters const &_parameters
)
{
	fcppt::cast::to_void(
		_environment.insert(
			std::move(
				_entity
			),
			_parameters
		)
	);
}

}

void
sanguis::server::environment::insert_no_result(
	sanguis::server::environment::object &_environment,
	sanguis::server::entities::with_id_unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_parameters
)
{
	insert_no_result_impl(
		_environment,
		std::move(
			_entity
		),
		_parameters
	);
}

void
sanguis::server::environment::insert_no_result(
	sanguis::server::environment::object &_environment,
	sanguis::server::entities::simple_unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_parameters
)
{
	insert_no_result_impl(
		_environment,
		std::move(
			_entity
		),
		_parameters
	);
}
