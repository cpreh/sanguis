#include "aoe_bullet.hpp"
#include "explosion.hpp"
#include "model/parameters.hpp"
#include "../z_ordering.hpp"
#include "../../next_id.hpp"
#include <fcppt/tr1/functional.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/make_auto_ptr.hpp>

sanguis::client::draw2d::entities::aoe_bullet::aoe_bullet(
	model::parameters const &_param,
	sprite::particle::system &_particle_system,
	insert_callback const &_insert,
	fcppt::string const &_name,
	funit const _aoe
)
:
	model::object(
		_param,
		_name,
		z_ordering::bullet,
		model::needs_healthbar::no,
		model::decay_option::immediate
	),
	model_collection_(_param.collection()),
	particle_system_(_particle_system),
	insert_(_insert),
	aoe_(_aoe)
{}
		
void
sanguis::client::draw2d::entities::aoe_bullet::on_decay()
{
	entities::auto_ptr explo(
		fcppt::make_auto_ptr<
			explosion
		>(
			std::tr1::ref(
				particle_system_
			),
			model_collection_,
			pos(),
			aoe_
		)
	);
	
	insert_(
		explo,
		client::next_id()
	);	
	
	model::object::on_decay();
}
