#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/entities/hover/name_and_health.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_name.hpp>


sanguis::client::draw2d::entities::hover::name_and_health::name_and_health(
	sanguis::client::draw2d::entities::hover::optional_name const &_name,
	sanguis::client::optional_health_pair const _health
)
:
	name_{
		_name
	},
	health_{
		_health
	}
{
}

sanguis::client::draw2d::entities::hover::optional_name const &
sanguis::client::draw2d::entities::hover::name_and_health::name() const
{
	return
		name_;
}

sanguis::client::optional_health_pair const
sanguis::client::draw2d::entities::hover::name_and_health::health() const
{
	return
		health_;
}
