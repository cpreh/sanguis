#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BASE_HPP_INCLUDED

#include <sanguis/client/draw2d/radius_fwd.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/create_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <fcppt/nonmovable.hpp>


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
	FCPPT_NONMOVABLE(
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

	[[nodiscard]]
	virtual
	bool
	dead() const = 0;

	[[nodiscard]]
	virtual
	sanguis::client::draw2d::sprite::center
	center() const = 0;

	[[nodiscard]]
	virtual
	sanguis::client::draw2d::radius
	radius() const = 0;

	virtual
	void
	pause(
		bool
	) = 0;

	[[nodiscard]]
	bool
	may_be_removed() const;

	[[nodiscard]]
	virtual
	sanguis::client::draw2d::entities::hover::optional_info
	hover() const;

	[[nodiscard]]
	virtual
	bool
	cursor_collision(
		sanguis::client::draw2d::sprite::center
	) const = 0;

	virtual
	void
	on_create(
		sanguis::client::draw2d::entities::create_parameters const &
	);

	virtual
	~base() = 0;
private:
	[[nodiscard]]
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
