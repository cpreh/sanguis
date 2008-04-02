#ifndef SANGUIS_ENTITY_TYPE_HPP_INCLUDED
#define SANGUIS_ENTITY_TYPE_HPP_INCLUDED

namespace sanguis
{

namespace entity_type {
enum type {
	player,
	bullet,
	wolf_white,
	wolf_black
};
}

entity_type::type get_unique_id();

}

#endif
