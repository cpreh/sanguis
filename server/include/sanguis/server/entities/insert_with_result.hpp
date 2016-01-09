#ifndef SANGUIS_SERVER_ENTITIES_INSERT_WITH_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_INSERT_WITH_RESULT_HPP_INCLUDED

#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/dynamic_cast.hpp>
#include <fcppt/optional/reference.hpp>
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
	typename Base,
	typename Entity,
	typename Object
>
fcppt::optional::reference<
	Entity
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
		fcppt::optional::dynamic_cast_<
			Entity
		>(
			_object.insert(
				fcppt::unique_ptr_to_base<
					Base
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
