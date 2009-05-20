#ifndef SANGUIS_SERVER_DAMAGE_WRAPPER_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_WRAPPER_HPP_INCLUDED

#include "wrapper_fwd.hpp"
#include "meta_fwd.hpp"
#include "value_type.hpp"
#include "../../damage_type.hpp"

namespace sanguis
{
namespace server
{
namespace damage
{

struct wrapper {
	wrapper(
		damage_type::type);
	
	meta const
	operator=(
		value_type) const;
private:
	damage_type::type const e;
};

}
}
}

#endif
