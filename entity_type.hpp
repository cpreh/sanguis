#ifndef SANGUIS_ENTITY_TYPE_HPP_INCLUDED
#define SANGUIS_ENTITY_TYPE_HPP_INCLUDED

namespace sanguis
{

namespace entity_type {
enum type {
	player,
	bullet,
	jackal,
	cursor,
	background,
	healthbar
};
}

entity_type::type get_unique_id();

}

#endif
