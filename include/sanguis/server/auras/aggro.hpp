#ifndef SANGUIS_SERVER_AURAS_AGGRO_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AGGRO_HPP_INCLUDED

#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/update_target_function.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class aggro
:
	public aura
{
	FCPPT_NONCOPYABLE(
		aggro
	);
public:
	aggro(
		server::radius,
		server::team::type,
		server::update_target_function const &add_target,
		server::update_target_function const &remove_target
	);

	~aggro();
private:
	void
	enter(
		entities::with_body &
	);

	void
	leave(
		entities::with_body &
	);

	update_target_function const
		add_target_,
		remove_target_;
};

}
}
}

#endif
