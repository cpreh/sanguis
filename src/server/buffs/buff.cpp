#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/entities/base_fwd.hpp>


void
sanguis::server::buffs::buff::add(
	sanguis::server::entities::base &
)
{
}

void
sanguis::server::buffs::buff::owner_lost()
{
}

void
sanguis::server::buffs::buff::remove(
	sanguis::server::entities::base &
)
{
}

void
sanguis::server::buffs::buff::update(
	sanguis::server::entities::base &
)
{
}

bool
sanguis::server::buffs::buff::expired() const
{
	return
		expired_;
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
