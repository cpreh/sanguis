#ifndef SANGUIS_SERVER_ENTITIES_EXP_AREA_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_EXP_AREA_HPP_INCLUDED

#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/player_fwd.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class exp_area
:
	public virtual sanguis::server::entities::with_ghosts,
	private sanguis::server::collision::ghost_base,
	private sanguis::server::entities::center_ghost
{
	FCPPT_NONCOPYABLE(
		exp_area
	);
public:
	explicit
	exp_area(
		sanguis::server::exp
	);

	~exp_area();
private:
	void
	remove()
	override;

	bool
	dead() const
	override;

	boost::logic::tribool const
	can_collide_with(
		sanguis::collision::world::body_base const &
	) const
	override;

	void
	body_enter(
		sanguis::collision::world::body_base &
	)
	override;

	void
	body_exit(
		sanguis::collision::world::body_base &
	)
	override;

	sanguis::server::exp const exp_;

	typedef
	std::unordered_map<
		sanguis::server::entities::player *,
		sanguis::server::entities::auto_weak_link
	> weak_link_map;

	weak_link_map player_links_;
};

}
}
}

#endif
