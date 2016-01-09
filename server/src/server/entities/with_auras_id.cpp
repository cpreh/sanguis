#include <sanguis/aura_type.hpp>
#include <sanguis/aura_type_vector.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_auras_id.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::world::body_enter_container
sanguis::server::entities::with_auras_id::add_aura(
	sanguis::server::auras::unique_ptr &&_aura
)
{
	fcppt::optional::maybe_void(
		_aura->type(),
		[
			this
		](
			sanguis::aura_type const _aura_type
		)
		{
			FCPPT_ASSERT_OPTIONAL_ERROR(
				this->environment()
			).get().add_aura(
				this->id(),
				_aura_type
			);
		}
	);

	return
		sanguis::server::entities::with_auras::add_aura(
			std::move(
				_aura
			)
		);
}

sanguis::server::entities::with_auras_id::with_auras_id(
	sanguis::server::auras::container &&_auras
)
:
	sanguis::server::entities::ifaces::with_id(),
	sanguis::server::entities::with_auras(
		std::move(
			_auras
		)
	)
{
}

sanguis::server::entities::with_auras_id::~with_auras_id()
{
}

sanguis::aura_type_vector
sanguis::server::entities::with_auras_id::aura_types() const
{
	return
		fcppt::algorithm::map_optional<
			sanguis::aura_type_vector
		>(
			this->auras(),
			[](
				sanguis::server::auras::unique_ptr const &_aura
			)
			{
				return
					_aura->type();
			}
		);
}
