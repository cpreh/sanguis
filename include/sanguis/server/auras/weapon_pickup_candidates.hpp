#ifndef SANGUIS_SERVER_AURAS_WEAPON_PICKUP_CANDIDATES_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_WEAPON_PICKUP_CANDIDATES_HPP_INCLUDED

#include <sanguis/collision/world/group_vector.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/weapon_pickup_add_candidate_callback.hpp>
#include <sanguis/server/auras/weapon_pickup_remove_candidate_callback.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

class weapon_pickup_candidates
:
	public sanguis::server::auras::aura
{
	FCPPT_NONCOPYABLE(
		weapon_pickup_candidates
	);
public:
	weapon_pickup_candidates(
		sanguis::server::radius,
		sanguis::server::auras::weapon_pickup_add_candidate_callback const &,
		sanguis::server::auras::weapon_pickup_remove_candidate_callback const &
	);

	~weapon_pickup_candidates();
private:
	sanguis::collision::world::group_vector
	collision_groups() const;

	void
	enter(
		sanguis::server::entities::with_body &
	);

	void
	leave(
		sanguis::server::entities::with_body &
	);

	sanguis::server::auras::weapon_pickup_add_candidate_callback const add_;

	sanguis::server::auras::weapon_pickup_remove_candidate_callback const remove_;
};

}
}
}

#endif
