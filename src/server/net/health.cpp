#include <sanguis/server/health.hpp>
#include <sanguis/server/net/health.hpp>
#include <sanguis/server/net/health_policy.hpp>
#include <sanguis/server/net/value_impl.hpp>


template
class
sanguis::server::net::value<
	sanguis::server::health,
	sanguis::server::net::health_policy
>;
