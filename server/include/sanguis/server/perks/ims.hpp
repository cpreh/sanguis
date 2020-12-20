#ifndef SANGUIS_SERVER_PERKS_IMS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IMS_HPP_INCLUDED

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

class ims
:
	public sanguis::server::perks::perk
{
	FCPPT_NONMOVABLE(
		ims
	);
public:
	ims();

	~ims()
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
