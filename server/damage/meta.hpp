#ifndef SANGUIS_SERVER_DAMAGE_META_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_META_HPP_INCLUDED

#include "meta_fwd.hpp"
#include "value_type.hpp"
#include "../../damage_type.hpp"

namespace sanguis
{
namespace server
{
namespace damage
{

struct meta
{
	meta(
		damage_type::type,
		value_type);
	
	damage_type::type type() const;
	value_type value() const;
private:
	damage_type::type e;
	value_type d;

};

}
}
}

#endif
