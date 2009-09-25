#include "with_perks.hpp"

sanguis::server::entities::with_perks::with_perks(
	base_parameters const &param_
)
:
	base(
		param_
	),
	perks_()
{}

void
sanguis::server::entities::with_perks::update(
	time_type const time
)
	BOOST_FOREACH(
		perk_container::reference p,
		perks_
	)
		p.second->apply(
			*this,
			time,
			environment()
		);
}

void
sanguis::server::entities::with_perks::add_perk(
	perks::auto_ptr p
)
{
	perk_type::type const type_(
		p->type()
	);

	perk_container::iterator it(
		perks_.find(
			type_
		)
	);

	if(it != perks_.end())
	{
		perks::perk &perk_(
			*it->second
		);

		if(perk_.can_raise_level())
			perk_.raise_level();
		else
		{
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< SGE_TEXT("Tried to raise perk level of a perk which can't do this.")
			);
		}
		return;
	}

	perks_.insert(
		type_,
		p
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

	return it == perks_.end()
		|| it->second->can_raise_level();
}
