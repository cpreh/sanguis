#include "enemy.hpp"
#include "../model.hpp"
#include "../z_ordering.hpp"
#include "../../enemy_type.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

namespace
{

sge::string const
get_model_name(
	sanguis::enemy_type::type);

}

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::enemy(
	entity_id const id,
	system &sys,
	enemy_type::type const etype)
{
	return entity_ptr(
		new model(
			id,
			sys,
			get_model_name(
				etype),
			z_ordering::model_generic));
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
	case sanguis::enemy_type::wolf_brown:
		return SGE_TEXT("wolf_brown");
	case sanguis::enemy_type::wolf_white:
		return SGE_TEXT("wolf_white");
	case sanguis::enemy_type::zombie00:
		return SGE_TEXT("zombie00");
	case sanguis::enemy_type::zombie01:
		return SGE_TEXT("zombie01");
	default:
		throw sge::exception(
			SGE_TEXT("draw::factory::enemy: missing loading code!"));
	}
}

}
