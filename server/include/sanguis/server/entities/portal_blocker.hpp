#ifndef SANGUIS_SERVER_ENTITIES_PORTAL_BLOCKER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PORTAL_BLOCKER_HPP_INCLUDED

#include <sanguis/server/entities/doodad.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities
{

class portal_blocker
:
	public sanguis::server::entities::doodad
{
	FCPPT_NONMOVABLE(
		portal_blocker
	);
public:
	explicit
	portal_blocker(
		sanguis::server::environment::load_context & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	~portal_blocker()
	override;
};

}

#endif
