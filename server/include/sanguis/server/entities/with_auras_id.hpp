#ifndef SANGUIS_SERVER_ENTITIES_WITH_AURAS_ID_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AURAS_ID_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/server/auras/create_callback_container.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_auras_id
:
	public virtual sanguis::server::entities::ifaces::with_id,
	public sanguis::server::entities::with_auras
{
	FCPPT_NONCOPYABLE(
		with_auras_id
	);
public:
	void
	add_aura(
		sanguis::server::auras::unique_ptr &&
	)
	override;
protected:
	explicit
	with_auras_id(
		sanguis::server::auras::create_callback_container const &
	);

	~with_auras_id();

	sanguis::aura_type_vector
	aura_types() const;
};

}
}
}

#endif
