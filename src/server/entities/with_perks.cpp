#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/perks/unique_ptr.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_perks::add_perk(
	sanguis::server::perks::unique_ptr &&_ptr
)
{
	sanguis::perk_type const ptype(
		_ptr->type()
	);

	perk_container::iterator it(
		perks_.find(
			ptype
		)
	);

	if(
		it == perks_.end()
	)
		it =
			fcppt::container::ptr::insert_unique_ptr_map(
				perks_,
				ptype,
				std::move(
					_ptr
				)
			).first;

	sanguis::server::perks::perk &ref(
		*it->second
	);

	ref.raise_level(
		*this
	);
}

sanguis::server::entities::with_perks::with_perks()
:
	sanguis::server::entities::base(),
	sanguis::server::entities::ifaces::with_team(),
	perks_()
{
}

sanguis::server::entities::with_perks::~with_perks()
{
}

void
sanguis::server::entities::with_perks::on_update()
{
	for(
		auto perk : perks_
	)
		perk->second->update(
			*this,
			this->environment()
		);
}
