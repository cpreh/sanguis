#include "with_body.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::server::entities::ifaces::with_body::with_body()
{
}

sanguis::server::entities::ifaces::with_body::~with_body()
{
}

sanguis::server::speed const
sanguis::server::entities::ifaces::with_body::initial_speed() const
{
	return
		server::speed(
			server::speed::value_type::null()
		);
}
