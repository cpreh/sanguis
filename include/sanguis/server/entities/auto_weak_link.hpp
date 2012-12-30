#ifndef SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_WEAK_LINK_HPP_INCLUDED

#include <sanguis/server/entities/auto_weak_hook.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
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
		sanguis::server::entities::base &ref
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

	sanguis::server::entities::base &
	operator*() const;

	sanguis::server::entities::base *
	operator->() const;

	sanguis::server::entities::base *
	get() const;

	explicit
	operator bool() const;
private:
	sanguis::server::entities::base &
	checked_ref() const;

	void
	add_me();

	sanguis::server::entities::base *ref_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
