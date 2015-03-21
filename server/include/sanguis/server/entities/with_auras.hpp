#ifndef SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED

#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/auras/aura_fwd.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/warn_unused_result.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_auras
:
	public virtual sanguis::server::entities::with_ghosts
{
	FCPPT_NONCOPYABLE(
		with_auras
	);
public:
	virtual
	sanguis::collision::world::body_enter_container
	add_aura(
		sanguis::server::auras::unique_ptr &&
	)
	FCPPT_PP_WARN_UNUSED_RESULT;
protected:
	explicit
	with_auras(
		sanguis::server::auras::container &&
	);

	~with_auras()
	override;

	sanguis::server::auras::container const &
	auras() const;
private:
	sanguis::server::auras::container auras_;
};

}
}
}

#endif
