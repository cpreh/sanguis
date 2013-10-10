#ifndef SANGUIS_SERVER_AURAS_SLOW_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_SLOW_HPP_INCLUDED

#include <sanguis/server/radius.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/buffs/provider.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

class slow
:
	public sanguis::server::auras::aura
{
	FCPPT_NONCOPYABLE(
		slow
	);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		sanguis::server::entities::property::value,
		factor
	);

	slow(
		sanguis::server::radius,
		sanguis::server::team,
		sanguis::server::auras::slow::factor
	);

	~slow();
private:
	void
	enter(
		sanguis::server::entities::with_body &
	);

	void
	leave(
		sanguis::server::entities::with_body &
	);

	sanguis::server::auras::slow::factor const factor_;

	sanguis::server::buffs::provider provider_;
};

}
}
}

#endif
