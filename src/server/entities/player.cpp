#include "player.hpp"
#include "circle_from_dim.hpp"
#include "default_solid.hpp"
#include "property/initial.hpp"
#include "../perks/perk.hpp"
#include "../perks/tree/create.hpp"
#include "../perks/tree/choosable.hpp"
#include "../perks/tree/choose.hpp"
#include "../perks/tree/status.hpp"
#include "../weapons/weapon.hpp"
#include "../environment/object.hpp"
#include "../environment/load_context.hpp"
#include "../level_calculate.hpp"
#include "../auras/update_sight.hpp"
#include "../../messages/add_player.hpp"
#include "../../messages/add_own_player.hpp"
#include "../../messages/create.hpp"
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::entities::player::player(
	server::environment::load_context &_load_context,
	server::health const _health,
	damage::armor const &_armor,
	entities::movement_speed const _speed,
	server::string const &_name,
	server::player_id const _player_id
)
:
	base(),
	with_auras(),
	with_body(
		entities::circle_from_dim(
			_load_context.entity_dim(
				FCPPT_TEXT("player")
			),
			entities::default_solid()
		)
	),
	with_buffs(),
	with_health(
		_health,
		_armor
	),
	with_perks(),
	with_velocity(
		property::initial(
			_speed.get(),
			0
		),
		server::direction(
			0
		)
	),
	with_weapon(
		weapons::unique_ptr()
	),
	name_(_name),
	player_id_(_player_id),
	exp_(0),
	level_(0),
	skill_points_(0),
	perk_tree_(
		perks::tree::create()
	)
{
	this->add_aura(
		auras::unique_ptr(
			fcppt::make_unique_ptr<
				auras::update_sight
			>(
				server::radius(
					1000 // FIXME
				),
				std::tr1::bind(
					&player::add_sight_range,
					this,
					std::tr1::placeholders::_1
				),
				std::tr1::bind(
					&player::remove_sight_range,
					this,
					std::tr1::placeholders::_1
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
	server::exp const _exp
)
{
	exp_ =
		server::exp(
			exp_.get()
			+ _exp.get()
		);

	this->environment().exp_changed(
		this->player_id(),
		this->id(),
		exp_
	);

	server::level const
		old_level(
			level_
		),
		new_level(
			server::level_calculate(
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
	perk_type::type const _perk
) const
{
	return
		skill_points_
		&&
		perks::tree::choosable(
			*perk_tree_,
			_perk,
			level_
		);
}

void
sanguis::server::entities::player::add_perk(
	perks::unique_ptr _ptr
)
{
	perks::tree::choose(
		*perk_tree_,
		_ptr->type()
	);

	with_perks::add_perk(
		move(
			_ptr
		)
	);

	--skill_points_;
}

sanguis::server::perks::tree::object const &
sanguis::server::entities::player::perk_tree() const
{
	return *perk_tree_;
}

sanguis::server::player_id
sanguis::server::entities::player::player_id() const
{
	return player_id_;
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
	entity_id const _entity_id
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
sanguis::server::entities::player::on_update(
	time_type const _time
)
{
	with_buffs::on_update(
		_time
	);

	with_health::on_update(
		_time
	);

	with_perks::on_update(
		_time
	);

	with_weapon::on_update(
		_time
	);
}

sanguis::messages::auto_ptr
sanguis::server::entities::player::add_message(
	server::player_id const _receiver
) const
{
	return
		_receiver == this->player_id()
		?
			player::make_add_message<
				messages::add_own_player
			>()
		:
			player::make_add_message<
				messages::add_player
			>();
}
sanguis::entity_type::type
sanguis::server::entities::player::type() const
{
	return entity_type::player;
}

sanguis::server::team::type
sanguis::server::entities::player::team() const
{
	return server::team::players;
}

void
sanguis::server::entities::player::on_new_weapon(
	weapon_type::type const _type
)
{
	this->environment().got_weapon(
		this->player_id(),
		this->id(),
		_type
	);
}

template<
	typename Message
>
sanguis::messages::auto_ptr
sanguis::server::entities::player::make_add_message() const
{
	return
		messages::create(
			Message(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->abs_speed().get(),
				this->current_health().get(),
				this->max_health().get()
			)
		);
}
