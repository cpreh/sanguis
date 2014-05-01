#ifndef SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_perks_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/perks/perk_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
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

	~with_perks();

	void
	update()
	override;
private:
	typedef boost::ptr_map<
		sanguis::perk_type,
		sanguis::server::perks::perk
	> perk_container;

	sanguis::random_generator &random_generator_;

	perk_container perks_;
};

}
}
}

#endif
