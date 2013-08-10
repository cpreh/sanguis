#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_VISITOR_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_VISITOR_HPP_INCLUDED

#include <sanguis/primary_weapon_type_fwd.hpp>
#include <sanguis/secondary_weapon_type_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace factory
{

class visitor
{
	FCPPT_NONASSIGNABLE(
		visitor
	);
public:
	explicit
	visitor(
		sanguis::server::weapons::factory::parameters const &
	);

	typedef
	sanguis::server::weapons::unique_ptr
	result_type;

	result_type
	operator()(
		sanguis::primary_weapon_type
	) const;

	result_type
	operator()(
		sanguis::secondary_weapon_type
	) const;
private:
	sanguis::server::weapons::factory::parameters const &parameters_;
};

}
}
}
}

#endif
