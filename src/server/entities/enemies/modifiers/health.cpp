#include <sanguis/server/health.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/health.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::modifiers::health(
	sanguis::server::entities::enemies::parameters &_parameters
)
{
	_parameters.health(
		sanguis::server::health(
			_parameters.health().get()
			*
			std::sqrt(
				_parameters.difficulty().get()
			)
		)
	);

	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("tough")
		);
}
