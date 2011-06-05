#include "with_auras.hpp"
#include "../auras/aura.hpp"
#include "../collision/ghost.hpp"
#include "../environment/object.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

void
sanguis::server::entities::with_auras::add_aura(
	auras::unique_ptr _aura
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		auras_,
		move(
			_aura
		)
	);

	auras::aura &ref(
		auras_.back()
	);

	ref.owner(
		this->id()
	);

	with_ghosts::add_ghost(
		ref.recreate()
	);
}

sanguis::server::entities::with_auras::with_auras()
:
	base(),
	auras_()
{
}

sanguis::server::entities::with_auras::~with_auras()
{
}
