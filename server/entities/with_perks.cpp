#include "with_perks.hpp"
#include "../perks/perk.hpp"
#include "../log.hpp"
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

void
sanguis::server::entities::with_perks::add_perk(
	perks::unique_ptr _ptr
)
{
	perk_type::type const ptype(
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
				move(
					_ptr
				)
			).first;

	perks::perk &ref(
		*it->second
	);

	if(
		!ref.can_raise_level()
	)	
	{
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("Tried to raise perk level of a perk which can't do this.")
		);

		return;
	}

	ref.raise_level(
		*this
	);
}

sanguis::server::entities::with_perks::with_perks()
:
	base(),
	perks_()
{}

sanguis::server::entities::with_perks::~with_perks()
{}

void
sanguis::server::entities::with_perks::on_update(
	time_type const time
)
{
	BOOST_FOREACH(
		perk_container::reference p,
		perks_
	)
		p.second->update(
			*this,
			time,
			environment()
		);
}

bool
sanguis::server::entities::with_perks::perk_choosable(
	perk_type::type const pt
) const
{
	perk_container::const_iterator const it(
		perks_.find(
			pt
		)
	);

	return
		it == perks_.end()
		|| it->second->can_raise_level();
}
