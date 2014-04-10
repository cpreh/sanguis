#ifndef SANGUIS_CLIENT_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace client
{

class world_parameters
{
	FCPPT_NONASSIGNABLE(
		world_parameters
	);
public:
	world_parameters(
		sanguis::world_id,
		sanguis::creator::top_parameters const &
	);

	sanguis::world_id const
	world_id() const;

	sanguis::creator::top_parameters const &
	top_parameters() const;
private:
	sanguis::world_id const world_id_;

	sanguis::creator::top_parameters const top_parameters_;
};

}
}

#endif
