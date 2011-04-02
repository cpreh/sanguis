#ifndef SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED

#include "with_dim_fwd.hpp"
#include "with_body.hpp"
#include "../dim.hpp"
#include "../pos.hpp"
#include "../radius.hpp"
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_dim
:
	public virtual entities::with_body 
{
	FCPPT_NONCOPYABLE(
		with_dim
	);
public:
	server::pos const
	pos() const;
protected:
	explicit with_dim(
		server::dim const &
	);

	~with_dim();

	server::dim const &
	dim() const;
private:
	sge::projectile::shape::shared_base_ptr const
	recreate_shape();


	server::dim const dim_;
};

}
}
}

#endif
