#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/messages/add_player.hpp>
#include <sanguis/messages/add_own_player.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/enter_sight_function.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/leave_sight_function.hpp>
#include <sanguis/server/level_calculate.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/update_sight.hpp>
#include <sanguis/server/collision/group.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/circle_from_dim.hpp>
#include <sanguis/server/entities/default_solid.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/property/initial.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/perks/tree/create.hpp>
#include <sanguis/server/perks/tree/choosable.hpp>
#include <sanguis/server/perks/tree/choose.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <sanguis/server/weapons/player_start_weapon.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length_square.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::player::player(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::health const _health,
	sanguis::server::damage::armor const &_armor,
	sanguis::server::entities::movement_speed const _speed,
	sanguis::server::string const &_name,
	sanguis::server::player_id const _player_id
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::body_velocity_combiner(),
	sanguis::server::entities::with_auras(),
	sanguis::server::entities::with_body(
		sanguis::server::entities::circle_from_dim(
			_load_context.entity_dim(
				sanguis::server::model_name(
					FCPPT_TEXT("player")
				)
			),
			sanguis::server::entities::default_solid()
		)
	),
	sanguis::server::entities::with_buffs(),
	sanguis::server::entities::with_id(
		_load_context.next_id()
	),
	sanguis::server::entities::with_health(
		_diff_clock,
		_health,
		_armor
	),
	sanguis::server::entities::with_links(),
	sanguis::server::entities::with_perks(),
	sanguis::server::entities::with_velocity(
		sanguis::server::entities::property::initial(
			sanguis::server::entities::property::initial::base(
				_speed.get()
			),
			sanguis::server::entities::property::initial::current(
				0.f
			)
		),
		sanguis::server::direction(
			0.f
		)
	),
	sanguis::server::entities::with_weapon(
		sanguis::server::weapons::player_start_weapon(
			_diff_clock
		)
	),
	name_(
		_name
	),
	player_id_(
		_player_id
	),
	exp_(
		0.f
	),
	level_(
		0u
	),
	skill_points_(
		0u
	),
	perk_tree_(
		sanguis::server::perks::tree::create()
	)
{
	this->add_aura(
		fcppt::make_unique_ptr<
			sanguis::server::auras::update_sight
		>(
			sanguis::server::radius(
				1000.f
			),
			sanguis::server::enter_sight_function(
				std::bind(
					&sanguis::server::entities::player::add_sight_range,
					this,
					std::placeholders::_1
				)
			),
			sanguis::server::leave_sight_function(
				std::bind(
					&sanguis::server::entities::player::remove_sight_range,
					this,
					std::placeholders::_1
				)
			)
		)
	);
}

sanguis::server::entities::player::~player()
{
}

void
sanguis::server::entities::player::add_exp(
	sanguis::server::exp const _exp
)
{
	exp_ =
		sanguis::server::exp(
			exp_.get()
			+ _exp.get()
		);

	this->environment().exp_changed(
		this->player_id(),
		this->id(),
		exp_
	);

	sanguis::server::level const
		old_level(
			level_
		),
		new_level(
			sanguis::server::level_calculate(
				exp_,
				old_level
			)
		);

	if(
		new_level == old_level
	)
		return;

	skill_points_ += new_level.get() - old_level.get();

	level_ = new_level;

	this->environment().level_changed(
		this->player_id(),
		this->id(),
		level_
	);
}

sanguis::server::string const
sanguis::server::entities::player::name() const
{
	return name_;
}

bool
sanguis::server::entities::player::perk_choosable(
	sanguis::perk_type const _perk
) const
{
	return
		skill_points_ > 0u
		&&
		sanguis::server::perks::tree::choosable(
			*perk_tree_,
			_perk,
			level_
		);
}

void
sanguis::server::entities::player::add_perk(
	sanguis::server::perks::unique_ptr &&_ptr
)
{
	sanguis::server::perks::tree::choose(
		*perk_tree_,
		_ptr->type()
	);

	sanguis::server::entities::with_perks::add_perk(
		std::move(
			_ptr
		)
	);

	--skill_points_;
}

void
sanguis::server::entities::player::center_from_client(
	sanguis::server::center const &_center
)
{
	// TODO: Make sure the new place is safe!
	if(
		fcppt::math::vector::length_square(
			(
				_center
				-
				this->center()
			).get()
		)
		<
		5.f
	)
		this->center(
			_center
		);
}

sanguis::server::perks::tree::object const &
sanguis::server::entities::player::perk_tree() const
{
	return *perk_tree_;
}

sanguis::server::player_id const
sanguis::server::entities::player::player_id() const
{
	return player_id_;
}

sanguis::server::team
sanguis::server::entities::player::team() const
{
	return sanguis::server::team::players;
}

void
sanguis::server::entities::player::on_remove()
{
	this->environment().remove_player(
		this->player_id()
	);
}

void
sanguis::server::entities::player::add_sight_range(
	sanguis::entity_id const _entity_id
)
{
	this->environment().add_sight_range(
		this->player_id(),
		_entity_id
	);
}

void
sanguis::server::entities::player::remove_sight_range(
	sanguis::entity_id const _entity_id
)
{
	this->environment().remove_sight_range(
		this->player_id(),
		_entity_id
	);
}

void
sanguis::server::entities::player::on_update()
{
	sanguis::server::entities::with_buffs::on_update();

	sanguis::server::entities::with_health::on_update();

	sanguis::server::entities::with_perks::on_update();

	sanguis::server::entities::with_weapon::on_update();
}

sanguis::messages::unique_ptr
sanguis::server::entities::player::add_message(
	sanguis::server::player_id const _receiver
) const
{
	return
		_receiver == this->player_id()
		?
			this->make_add_message<
				sanguis::messages::add_own_player
			>()
		:
			this->make_add_message<
				sanguis::messages::add_player
			>();
}

void
sanguis::server::entities::player::on_new_weapon(
	sanguis::server::weapons::weapon const &_weapon
)
{
	// TODO: Generate a helpful text about what the weapon's attributes are
/*
	this->environment().got_weapon(
		this->player_id(),
		this->id(),
		_type
	);*/
}

sanguis::server::collision::group_vector
sanguis::server::entities::player::collision_groups() const
{
	return
		sanguis::server::collision::group_vector{
			sanguis::server::collision::group::player
		};
}

template<
	typename Message
>
sanguis::messages::unique_ptr
sanguis::server::entities::player::make_add_message() const
{
	return
		sanguis::messages::create(
			Message(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->speed().get(),
				this->current_health().get(),
				this->max_health().get(),
				this->primary_weapon_type()
			)
		);
}
