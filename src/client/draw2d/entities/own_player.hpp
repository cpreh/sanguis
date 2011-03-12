#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_PLAYER_HPP_INCLUDED

#include "player.hpp"
#include "model/parameters_fwd.hpp"
#include "../transform_callback.hpp"
#include "../../../time_type.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class own_player
:
	public player
{
	FCPPT_NONCOPYABLE(
		own_player
	);
public:
	explicit own_player(
		model::parameters const &,
		transform_callback const &
	);

	~own_player();
private:
	void
	update(
		time_type
	);

	transform_callback const transform_;
};

}
}
}
}

#endif
