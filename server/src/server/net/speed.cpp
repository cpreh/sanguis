#include <sanguis/server/speed.hpp>
#include <sanguis/server/net/speed.hpp>
#include <sanguis/server/net/speed_policy.hpp>
#include <sanguis/server/net/value_impl.hpp>


template
class
sanguis::server::net::value<
	sanguis::server::speed,
	sanguis::server::net::speed_policy
>;
