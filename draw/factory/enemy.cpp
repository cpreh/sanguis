#include "enemy.hpp"
#include "../model.hpp"
#include "../../enemy_type.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

namespace
{

sge::string const
get_model_name(
	sanguis::enemy_type::type);

}

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::enemy(
	entity_id const id,
	enemy_type::type const etype)
{
	return entity_ptr(
		new model(
			id,
			get_model_name(
				etype)));
}

namespace
{

sge::string const
get_model_name(
	sanguis::enemy_type::type const etype)
{
	switch(etype) {
	case sanguis::enemy_type::wolf_black:
		return SGE_TEXT("wolf_black");
	case sanguis::enemy_type::wolf_white:
		return SGE_TEXT("wolf_white");
	case sanguis::enemy_type::zombie:
		return SGE_TEXT("zombie00");
	default:
		throw sge::exception(
			SGE_TEXT("draw::factory::enemy: missing loading code!"));
	}
}

}
