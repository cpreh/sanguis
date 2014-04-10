#include <sanguis/server/center.hpp>
#include <sanguis/server/net/center.hpp>
#include <sanguis/server/net/center_policy.hpp>
#include <sanguis/server/net/value_impl.hpp>


template
class
sanguis::server::net::value<
	sanguis::server::center,
	sanguis::server::net::center_policy
>;
