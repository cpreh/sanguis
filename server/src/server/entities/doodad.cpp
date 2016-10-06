#include <sanguis/doodad_type.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/load/model/doodad_path.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/created.hpp>
#include <sanguis/messages/roles/doodad_type.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/server/add_doodad.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/optional_mass.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/entities/doodad.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <alda/message/init_record.hpp>


sanguis::server::entities::doodad::doodad(
	sanguis::server::environment::load_context &_load_context,
	sanguis::doodad_type const _doodad_type
)
:
	sanguis::server::entities::with_body(
		_load_context.model_size(
			sanguis::load::model::doodad_path(
				_doodad_type
			)
		),
		sanguis::server::optional_mass()
	),
	sanguis::server::entities::with_id(
		_load_context.next_id()
	),
	sanguis::server::entities::with_links(),
	doodad_type_{
		_doodad_type
	},
	dead_{
		false
	}
{
}

sanguis::server::entities::doodad::~doodad()
{
}

void
sanguis::server::entities::doodad::kill()
{
	dead_ =
		true;
}

bool
sanguis::server::entities::doodad::dead() const
{
	return
		dead_;
}

void
sanguis::server::entities::doodad::update()
{
	sanguis::server::entities::with_body::update();
}

sanguis::collision::world::body_group
sanguis::server::entities::doodad::collision_group() const
{
	return
		sanguis::collision::world::body_group::doodad;
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::doodad::add_message(
	sanguis::server::player_id,
	sanguis::collision::world::created const _created
) const
{
	return
		sanguis::messages::server::create_ptr(
			alda::message::init_record<
				sanguis::messages::server::add_doodad
			>(
				sanguis::messages::roles::entity_id{} =
					this->id(),
				sanguis::messages::roles::center{} =
					this->center().get(),
				sanguis::messages::roles::angle{} =
					0.f, // TODO: Should center_ghost save the angle?
				sanguis::messages::roles::created{} =
					_created.get(),
				sanguis::messages::roles::doodad_type{} =
					doodad_type_
			)
		);
}
