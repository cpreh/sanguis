#include "weapon_pickup.hpp"
#include "simple_sprite.hpp"
#include "../z_ordering.hpp"
#include "../../weapon_type.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

namespace
{

sge::string const get_texture(
	sanguis::weapon_type::type);

}

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::weapon_pickup(
	entity_id const id,
	weapon_type::type const wtype)
{
	return simple_sprite(
		id,
		z_ordering::pickup,
			get_texture(
				wtype));
}

namespace
{

sge::string const get_texture(
	sanguis::weapon_type::type const wtype)
{
	switch(wtype) {
	case sanguis::weapon_type::pistol:
		return SGE_TEXT("pistol_pickup");
	case sanguis::weapon_type::shotgun:
		return SGE_TEXT("shotgun_pickup");
	default:
		throw sge::exception(
			SGE_TEXT("draw::factory::weapon_pickup: missing loading code!"));
	}
}

}
