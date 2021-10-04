#ifndef SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED

#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/auras/aura_fwd.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities
{

class with_auras
:
	public virtual sanguis::server::entities::with_ghosts
{
	FCPPT_NONMOVABLE(
		with_auras
	);
public:
	[[nodiscard]]
	virtual
	sanguis::collision::world::body_enter_container
	add_aura(
		sanguis::server::auras::unique_ptr &&
	);
protected:
	explicit
	with_auras(
		sanguis::server::auras::container &&
	);

	~with_auras()
	override;

	[[nodiscard]]
	sanguis::server::auras::container const &
	auras() const;
private:
	sanguis::server::auras::container auras_;
};

}

#endif
