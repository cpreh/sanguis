#ifndef SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED

#include "with_dim_fwd.hpp"
#include "base.hpp"
#include "../dim.hpp"
#include "../pos.hpp"
#include "../radius.hpp"
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
	public virtual base
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
	server::radius const
	radius() const;

	server::dim const dim_;
};

}
}
}

#endif
