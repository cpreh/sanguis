#ifndef SANGUIS_SERVER_DAMAGE_META_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_META_HPP_INCLUDED

#include <sanguis/server/damage/meta_fwd.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit.hpp>


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
		sanguis::server::damage::type,
		sanguis::server::damage::unit
	);

	sanguis::server::damage::type
	type() const;

	sanguis::server::damage::unit
	value() const;
private:
	sanguis::server::damage::type type_;

	sanguis::server::damage::unit value_;

};

}
}
}

#endif
