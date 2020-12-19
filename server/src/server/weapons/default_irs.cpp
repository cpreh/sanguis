#include <sanguis/server/weapons/default_irs.hpp>
#include <sanguis/server/weapons/irs.hpp>


sanguis::server::weapons::irs
sanguis::server::weapons::default_irs()
{
	return
		sanguis::server::weapons::irs(
			1.F
		);
}
