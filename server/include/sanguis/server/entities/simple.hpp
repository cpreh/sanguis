#ifndef SANGUIS_SERVER_ENTITIES_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SIMPLE_HPP_INCLUDED

#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/simple_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class simple
:
	public virtual sanguis::server::entities::base
{
	FCPPT_NONMOVABLE(
		simple
	);
protected:
	simple();
public:
	~simple()
	override;
};

}
}
}

#endif
