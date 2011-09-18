#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>

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
sanguis::server::entities::with_perks::on_update()
{
	for(
		perk_container::iterator it(
			perks_.begin()
		);
		it != perks_.end();
		++it
	)
		it->second->update(
			*this,
			this->environment()
		);
}
