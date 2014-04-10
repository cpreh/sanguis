#include <sanguis/server/buffs/buff.hpp>


void
sanguis::server::buffs::buff::add()
{
	this->apply(
		sanguis::server::buffs::buff::added(
			true
		)
	);
}

void
sanguis::server::buffs::buff::remove()
{
	this->apply(
		sanguis::server::buffs::buff::added(
			false
		)
	);
}

void
sanguis::server::buffs::buff::update()
{
}

sanguis::server::buffs::buff::~buff()
{
}

sanguis::server::buffs::buff::buff()
{
}

void
sanguis::server::buffs::buff::apply(
	sanguis::server::buffs::buff::added
)
{
}
