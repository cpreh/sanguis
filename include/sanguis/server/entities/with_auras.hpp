#ifndef SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED

#include <sanguis/server/auras/aura_fwd.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_auras
:
	public virtual sanguis::server::entities::with_ghosts
{
	FCPPT_NONCOPYABLE(
		with_auras
	);
public:
	void
	add_aura(
		sanguis::server::auras::unique_ptr &&
	);
protected:
	with_auras();

	~with_auras();
private:
	typedef boost::ptr_list<
		sanguis::server::auras::aura
	> aura_container;

	aura_container auras_;
};

}
}
}

#endif
