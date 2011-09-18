#ifndef SANGUIS_SERVER_AURAS_UPDATE_SIGHT_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_UPDATE_SIGHT_HPP_INCLUDED

#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/update_sight_function.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class update_sight
:
	public aura
{
	FCPPT_NONCOPYABLE(
		update_sight
	);
public:
	update_sight(
		server::radius,
		update_sight_function const &enter,
		update_sight_function const &leave
	);

	~update_sight();
private:
	collision::group_vector const
	collision_groups() const;

	void
	enter(
		entities::with_body &
	);

	void
	leave(
		entities::with_body &
	);

	update_sight_function const
		enter_,
		leave_;
};

}
}
}

#endif
