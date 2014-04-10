#ifndef SANGUIS_SERVER_ENTITIES_INSERT_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_INSERT_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class insert_parameters
{
	FCPPT_NONASSIGNABLE(
		insert_parameters
	);
public:
	insert_parameters(
		sanguis::server::center const &,
		sanguis::server::angle
	);

	sanguis::server::center const &
	center() const;

	server::angle const
	angle() const;
private:
	sanguis::server::center const center_;

	sanguis::server::angle const angle_;
};

}
}
}

#endif
