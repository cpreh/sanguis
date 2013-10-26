#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BASE_HPP_INCLUDED

#include <sanguis/client/draw2d/radius_fwd.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/name_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	void
	update() = 0;

	void
	die();

	virtual
	bool
	dead() const = 0;

	bool
	may_be_removed() const;

	virtual
	sanguis::client::draw2d::entities::name
	name() const;

	virtual
	sanguis::client::draw2d::sprite::center const
	center() const = 0;

	virtual
	sanguis::client::draw2d::radius const
	radius() const = 0;

	virtual
	~base() = 0;
private:
	virtual
	bool
	is_decayed() const = 0;

	virtual
	void
	on_die() = 0;
};

}
}
}
}

#endif
