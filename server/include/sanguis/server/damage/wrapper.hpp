#ifndef SANGUIS_SERVER_DAMAGE_WRAPPER_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_WRAPPER_HPP_INCLUDED

#include <sanguis/server/damage/armor_meta_fwd.hpp>
#include <sanguis/server/damage/armor_unit_fwd.hpp>
#include <sanguis/server/damage/meta_fwd.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit_fwd.hpp>
#include <sanguis/server/damage/wrapper_fwd.hpp>
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
	);
public:
	explicit
	wrapper(
		sanguis::server::damage::type
	);

	sanguis::server::damage::meta const
	operator=(
		sanguis::server::damage::unit
	) const;

	sanguis::server::damage::armor_meta const
	operator=(
		sanguis::server::damage::armor_unit
	) const;
private:
	sanguis::server::damage::type const type_;
};

}
}
}

#endif
