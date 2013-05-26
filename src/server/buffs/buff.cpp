#include <sanguis/server/buffs/buff.hpp>


bool
sanguis::server::buffs::buff::expired() const
{
	return expired_;
}

sanguis::server::buffs::buff::~buff()
{
}

sanguis::server::buffs::buff::buff()
:
	expired_(
		false
	)
{
}

void
sanguis::server::buffs::buff::expire()
{
	expired_ = true;
}
