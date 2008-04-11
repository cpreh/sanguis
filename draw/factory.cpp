#include "bullet.hpp"
#include "factory.hpp"
#include "player.hpp"
#include "model.hpp"
#include "coord_transform.hpp"
#include "../entity_type.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::create_entity(
	const entity_id id,
	const entity_type::type type)
{
	// TODO: make this prettier and generate code for it using a template
	switch(type) {
	case entity_type::player:
		return entity_ptr(
			new player(id));
	case entity_type::bullet:
		return entity_ptr(
			new bullet(id));
	case entity_type::wolf_white:
		return entity_ptr(
			new model(
				id,
				SGE_TEXT("wolf_white")));
	case entity_type::wolf_black:
		return entity_ptr(
			new model(
				id,
				SGE_TEXT("wolf_black")));
	case entity_type::zombie:
		return entity_ptr(
			new model(
				id,
				SGE_TEXT("zombie00"))); // FIXME
	default:
		throw sge::exception(SGE_TEXT("draw::factory: missing loading code!"));
	}
}
