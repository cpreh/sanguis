#ifndef SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_perks_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_health.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/ifaces/with_velocity.hpp>
#include <sanguis/server/entities/ifaces/with_weapon.hpp>
#include <sanguis/server/perks/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_perks
:
	public virtual sanguis::server::entities::base,
	public virtual sanguis::server::entities::ifaces::with_health,
	public virtual sanguis::server::entities::ifaces::with_velocity,
	public virtual sanguis::server::entities::ifaces::with_weapon,
	public virtual sanguis::server::entities::ifaces::with_team
{
	FCPPT_NONCOPYABLE(
		with_perks
	);
public:
	void
	add_perk(
		sanguis::perk_type
	);
protected:
	explicit
	with_perks(
		sanguis::random_generator &
	);

	~with_perks()
	override;

	void
	update()
	override;
private:
	using
	perk_container
	=
	std::map<
		sanguis::perk_type,
		sanguis::server::perks::unique_ptr
	>;

	sanguis::random_generator &random_generator_;

	perk_container perks_;
};

}
}
}

#endif
