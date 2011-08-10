#ifndef SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED

#include "auto_weak_hook.hpp"
#include "base_fwd.hpp"
#include <fcppt/safe_bool.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class auto_weak_link
:
	public auto_weak_hook
{
	FCPPT_SAFE_BOOL(
		auto_weak_link
	)
public:
	auto_weak_link();

	explicit auto_weak_link(
		base &ref
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

	base &
	operator*() const;

	base *
	operator->() const;

	base *
	get() const;
private:
	base &
	checked_ref() const;

	void
	add_me();

	bool
	boolean_test() const;

	base *ref_;
};

}
}
}

#endif
