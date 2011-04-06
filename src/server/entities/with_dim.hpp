#ifndef SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_DIM_HPP_INCLUDED

#include "with_dim_fwd.hpp"
#include "with_body.hpp"
#include "../collision/solidity_fwd.hpp"
#include "../dim.hpp"
#include "../pos.hpp"
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
	public entities::with_body
{
	FCPPT_NONCOPYABLE(
		with_dim
	);
public:
	server::pos const
	pos() const;
protected:
	explicit with_dim(
		collision::solidity const &,
		server::dim const &
	);

	~with_dim();

	server::dim const &
	dim() const;
private:
	server::dim const dim_;
};

}
}
}

#endif
