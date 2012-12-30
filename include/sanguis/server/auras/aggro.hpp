#ifndef SANGUIS_SERVER_AURAS_AGGRO_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AGGRO_HPP_INCLUDED

#include <sanguis/server/radius.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/update_target_function.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

class aggro
:
	public sanguis::server::auras::aura
{
	FCPPT_NONCOPYABLE(
		aggro
	);
public:
	aggro(
		sanguis::server::radius,
		sanguis::server::team,
		sanguis::server::update_target_function const &add_target,
		sanguis::server::update_target_function const &remove_target
	);

	~aggro();
private:
	void
	enter(
		sanguis::server::entities::with_body &
	);

	void
	leave(
		sanguis::server::entities::with_body &
	);

	sanguis::server::update_target_function const
		add_target_,
		remove_target_;
};

}
}
}

#endif
