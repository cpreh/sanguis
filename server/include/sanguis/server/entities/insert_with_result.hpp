#ifndef SANGUIS_SERVER_ENTITIES_INSERT_WITH_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_INSERT_WITH_RESULT_HPP_INCLUDED

#include <sanguis/exception.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/optional/to_exception.hpp>
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
		fcppt::optional::map(
			_object.insert(
				fcppt::unique_ptr_to_base<
					Base
				>(
					std::move(
						_entity
					)
				),
				_parameters
			),
			[](
				// TODO(philipp)
				auto const &_inserted
			)
			->
			fcppt::reference<
				Entity
			>
			{
				return
					fcppt::optional::to_exception(
						fcppt::cast::dynamic<
							Entity
						>(
							_inserted.get()
						),
						[]{
							return
								sanguis::exception{
									FCPPT_TEXT("Invalid dynamic_cast in insert_with_result")
								};
						}
					);
			}
		);
}

}
}
}

#endif
