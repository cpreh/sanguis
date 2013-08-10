#ifndef SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED

#include <sanguis/server/entities/auto_weak_hook.hpp>
#include <sanguis/server/entities/with_links_fwd.hpp>
#include <fcppt/optional_impl.hpp>
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

	typedef
	fcppt::optional<
		sanguis::server::entities::with_links &
	>
	optional_with_links_ref;

	sanguis::server::entities::with_links &
	operator*() const;

	sanguis::server::entities::auto_weak_link::optional_with_links_ref const
	operator->() const;

	sanguis::server::entities::auto_weak_link::optional_with_links_ref const
	get() const;

	explicit
	operator bool() const;
private:
	sanguis::server::entities::with_links &
	checked_ref() const;

	void
	add_me();

	sanguis::server::entities::auto_weak_link::optional_with_links_ref ref_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
