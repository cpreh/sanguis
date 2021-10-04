#ifndef SANGUIS_SERVER_WEAPONS_ATTRIBUTES_BASIC_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTRIBUTES_BASIC_DECL_HPP_INCLUDED

#include <sanguis/server/weapons/attributes/basic_fwd.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace sanguis::server::weapons::attributes
{

template<
	typename Wrapped
>
class basic
{
public:
	explicit
	basic(
		Wrapped
	);

	void
	extra(
		Wrapped
	);

	using
	optional_extra
	=
	fcppt::optional::object<
		Wrapped
	>;

	[[nodiscard]]
	Wrapped
	base() const;

	[[nodiscard]]
	optional_extra
	extra() const;

	[[nodiscard]]
	Wrapped
	value() const;
private:
	Wrapped base_;

	optional_extra extra_;
};

}

#endif
