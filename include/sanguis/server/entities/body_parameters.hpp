#ifndef SANGUIS_SERVER_ENTITIES_BODY_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BODY_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/radius.hpp>
#include <sanguis/server/entities/body_parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class body_parameters
{
	FCPPT_NONASSIGNABLE(
		body_parameters
	);
public:
	explicit
	body_parameters(
		sanguis::server::radius
	);

	sanguis::server::radius const
	radius() const;
private:
	sanguis::server::radius const radius_;
};

}
}
}

#endif
