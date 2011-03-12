#ifndef SANGUIS_SERVER_DAMAGE_WRAPPER_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_WRAPPER_HPP_INCLUDED

#include "wrapper_fwd.hpp"
#include "meta_fwd.hpp"
#include "unit.hpp"
#include "../../damage_type.hpp"
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace server
{
namespace damage
{

class wrapper
{
	FCPPT_NONASSIGNABLE(
		wrapper
	)
public:
	wrapper(
		damage_type::type
	);
	
	meta const
	operator=(
		unit
	) const;
private:
	damage_type::type const type_;
};

}
}
}

#endif
