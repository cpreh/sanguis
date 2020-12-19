#ifndef SANGUIS_SERVER_ENTITIES_WITH_LINKS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_LINKS_HPP_INCLUDED

#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/link_container.hpp>
#include <sanguis/server/entities/with_links_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_links
:
	public virtual sanguis::server::entities::base,
	public virtual sanguis::server::entities::ifaces::with_links
{
	FCPPT_NONMOVABLE(
		with_links
	);
protected:
	with_links();
public:
	~with_links()
	override = 0;

	[[nodiscard]]
	sanguis::server::entities::auto_weak_link
	link()
	final;
protected:
	void
	reset_links()
	override;
private:
	friend class sanguis::server::entities::auto_weak_link;

	void
	insert_link(
		sanguis::server::entities::auto_weak_link & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	sanguis::server::entities::link_container links_;
};

}
}
}

#endif
