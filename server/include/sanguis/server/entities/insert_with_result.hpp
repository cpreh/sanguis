#ifndef SANGUIS_SERVER_ENTITIES_INSERT_WITH_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_INSERT_WITH_RESULT_HPP_INCLUDED

#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <fcppt/dynamic_optional_cast.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

template<
	typename Entity,
	typename Object
>
fcppt::optional<
	Entity &
>
insert_with_result(
	Object &_object,
	fcppt::unique_ptr<
		Entity
	> &&_entity,
	sanguis::server::entities::insert_parameters const &_parameters
)
{
	return
		fcppt::dynamic_optional_cast<
			Entity
		>(
			_object.insert(
				fcppt::unique_ptr_to_base<
					sanguis::server::entities::base
				>(
					std::move(
						_entity
					)
				),
				_parameters
			)
		);
}

}
}
}

#endif
