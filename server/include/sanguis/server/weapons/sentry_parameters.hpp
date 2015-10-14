#ifndef SANGUIS_SERVER_WEAPONS_SENTRY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SENTRY_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/sentry_parameters_fwd.hpp>
#include <sanguis/server/weapons/attributes/health.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class sentry_parameters
{
	FCPPT_NONASSIGNABLE(
		sentry_parameters
	);
public:
	sentry_parameters(
		sanguis::server::health,
		sanguis::server::weapons::backswing_time,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::range
	);

	sanguis::server::weapons::attributes::health
	health() const;

	sanguis::server::weapons::backswing_time
	backswing_time() const;

	sanguis::server::weapons::cast_point
	cast_point() const;

	sanguis::server::weapons::range
	range() const;

	void
	extra_health(
		sanguis::server::health
	);
private:
	sanguis::server::weapons::attributes::health health_;

	sanguis::server::weapons::backswing_time const backswing_time_;

	sanguis::server::weapons::cast_point const cast_point_;

	sanguis::server::weapons::range const range_;
};

}
}
}

#endif
