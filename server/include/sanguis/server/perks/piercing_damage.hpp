#ifndef SANGUIS_SERVER_PERKS_PIERCING_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_PIERCING_DAMAGE_HPP_INCLUDED

#include <sanguis/server/entities/with_perks_fwd.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{

class piercing_damage
:
	public sanguis::server::perks::perk
{
	FCPPT_NONMOVABLE(
		piercing_damage
	);
public:
	piercing_damage();

	~piercing_damage()
	override;
private:
	void
	change(
		sanguis::server::entities::with_perks &, // NOLINT(google-runtime-references)
		sanguis::server::perks::level_diff
	)
	override;
};

}
}
}

#endif
