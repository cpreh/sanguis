#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/draw2d/entities/model/health_pair.hpp>


sanguis::client::draw2d::entities::model::health_pair::health_pair(
	sanguis::client::health const _health,
	sanguis::client::max_health const _max_health
)
:
	health_(
		_health
	),
	max_health_(
		_max_health
	)
{
}

sanguis::client::health const
sanguis::client::draw2d::entities::model::health_pair::health() const
{
	return
		health_;
}

sanguis::client::max_health const
sanguis::client::draw2d::entities::model::health_pair::max_health() const
{
	return
		max_health_;
}
