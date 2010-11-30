#ifndef SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED

#include "base_fwd.hpp"
#include <boost/intrusive/list_hook.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef boost::intrusive::list_base_hook<
	boost::intrusive::link_mode<
		boost::intrusive::auto_unlink
	>
> auto_hook_type;

class auto_weak_link
:
	public auto_hook_type
{
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
private:
	struct unspecified {};
public:
	operator unspecified *() const;

	base &
	operator*() const;

	base *
	operator->() const;

	base *
	get() const;
private:
	base &
	checked_ref() const;

	void add_me();

	base *ref_;
};

}
}
}

#endif
