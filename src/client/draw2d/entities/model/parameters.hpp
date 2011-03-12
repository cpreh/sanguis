#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PARAMETERS_HPP_INCLUDED

#include "parameters_fwd.hpp"
#include "../../sprite/normal/system.hpp"
#include "../../sprite/colored/system.hpp"
#include "../../../../load/model/collection_fwd.hpp"
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	explicit parameters(
		sprite::colored::system &,
		sprite::normal::system &,
		load::model::collection const &
	);

	sprite::colored::system &
	colored_system() const;

	sprite::normal::system &
	normal_system() const;

	load::model::collection const &
	collection() const;
private:
	sprite::colored::system &colored_system_;

	sprite::normal::system &normal_system_;
	
	load::model::collection const &collection_;
};

}
}
}
}
}

#endif
