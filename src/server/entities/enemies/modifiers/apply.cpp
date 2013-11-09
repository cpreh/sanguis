#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/apply.hpp>
#include <sanguis/server/entities/enemies/modifiers/container.hpp>


sanguis::server::entities::enemies::attribute_container
sanguis::server::entities::enemies::modifiers::apply(
	sanguis::server::entities::enemies::parameters &_parameters,
	sanguis::server::entities::enemies::modifiers::container const &_modifiers
)
{
	sanguis::server::entities::enemies::attribute_container result;

	result.reserve(
		_modifiers.size()
	);

	for(
		auto const &modifier
		:
		_modifiers
	)
		result.push_back(
			modifier(
				_parameters
			)
		);

	return
		result;
}
