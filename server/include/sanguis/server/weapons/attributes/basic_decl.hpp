#ifndef SANGUIS_SERVER_WEAPONS_ATTRIBUTES_BASIC_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTRIBUTES_BASIC_DECL_HPP_INCLUDED

#include <sanguis/server/weapons/attributes/basic_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace attributes
{

template<
	typename Wrapped
>
class basic
{
	FCPPT_NONASSIGNABLE(
		basic
	);
public:
	explicit
	basic(
		Wrapped
	);

	void
	extra(
		Wrapped
	);

	typedef
	fcppt::optional::object<
		Wrapped
	>
	optional_extra;

	Wrapped
	base() const;

	optional_extra
	extra() const;

	Wrapped
	value() const;
private:
	Wrapped const base_;

	optional_extra extra_;
};

}
}
}
}

#endif
