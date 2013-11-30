#include <sanguis/server/regeneration.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/regenerating.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::modifiers::regenerating(
	sanguis::server::entities::enemies::parameters &_parameters
)
{
	_parameters.regeneration(
		sanguis::server::regeneration(
			std::sqrt(
				_parameters.difficulty().get()
			)
		)
	);

	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("regenerating")
		);
}
