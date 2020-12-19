#ifndef SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED

#include <sanguis/server/entities/auto_weak_hook.hpp>
#include <sanguis/server/entities/with_links_fwd.hpp>
#include <fcppt/optional/reference.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
class auto_weak_link
:
	public sanguis::server::entities::auto_weak_hook
{
public:
	using
	optional_with_links_ref
	=
	fcppt::optional::reference<
		sanguis::server::entities::with_links
	>;

	auto_weak_link();

	explicit
	auto_weak_link(
		sanguis::server::entities::with_links &ref // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

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

	[[nodiscard]]
	optional_with_links_ref
	get() const;

	[[nodiscard]]
	bool
	operator==(
		sanguis::server::entities::auto_weak_link const &
	) const;
private:
	[[nodiscard]]
	sanguis::server::entities::with_links &
	checked_ref() const;

	void
	add_me();

	optional_with_links_ref ref_;
};

bool
operator!=(
	sanguis::server::entities::auto_weak_link const &,
	sanguis::server::entities::auto_weak_link const &
);

}
}
}

#endif
