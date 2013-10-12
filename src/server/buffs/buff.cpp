#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/entities/base_fwd.hpp>


void
sanguis::server::buffs::buff::add(
	sanguis::server::entities::base &_base
)
{
	this->apply(
		_base,
		sanguis::server::buffs::buff::added(
			true
		)
	);
}

void
sanguis::server::buffs::buff::remove(
	sanguis::server::entities::base &_base
)
{
	this->apply(
		_base,
		sanguis::server::buffs::buff::added(
			false
		)
	);
}

void
sanguis::server::buffs::buff::update(
	sanguis::server::entities::base &
)
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
	sanguis::server::entities::base &,
	sanguis::server::buffs::buff::added
)
{
}
