#ifndef SANGUIS_SERVER_DAMAGE_META_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_META_HPP_INCLUDED

#include <sanguis/server/damage/meta_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/damage_type.hpp>

namespace sanguis
{
namespace server
{
namespace damage
{

class meta
{
public:
	meta(
		damage_type::type,
		unit
	);

	damage_type::type
	type() const;

	unit
	value() const;
private:
	damage_type::type type_;

	unit value_;

};

}
}
}

#endif
