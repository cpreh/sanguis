#ifndef SANGUIS_SERVER_ENTITIES_INSERT_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_INSERT_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <fcppt/math/vector/object_decl.hpp>
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
		server::center const &,
		server::angle
	);

	server::center const &
	center() const;

	server::angle const
	angle() const;
private:
	server::center const center_;

	server::angle const angle_;
};

}
}
}

#endif
