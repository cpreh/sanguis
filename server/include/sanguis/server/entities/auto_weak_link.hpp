#ifndef SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED

#include <sanguis/server/entities/auto_weak_hook.hpp>
#include <sanguis/server/entities/with_links_fwd.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class auto_weak_link
:
	public sanguis::server::entities::auto_weak_hook
{
public:
	typedef
	fcppt::optional<
		sanguis::server::entities::with_links &
	>
	optional_with_links_ref;

	auto_weak_link();

	explicit
	auto_weak_link(
		sanguis::server::entities::with_links &ref
	);

	auto_weak_link(
		auto_weak_link const &
	);

	~auto_weak_link();

	auto_weak_link &
	operator=(
		auto_weak_link const &
	);

	void
	unlink();

	optional_with_links_ref const
	get() const;

	bool
	operator==(
		sanguis::server::entities::auto_weak_link const &
	) const;
private:
	sanguis::server::entities::with_links &
	checked_ref() const;

	void
	add_me();

	optional_with_links_ref ref_;
};

FCPPT_PP_POP_WARNING

bool
operator!=(
	sanguis::server::entities::auto_weak_link const &,
	sanguis::server::entities::auto_weak_link const &
);

}
}
}

#endif
