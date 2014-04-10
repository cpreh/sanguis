#ifndef SANGUIS_SERVER_NET_VALUE_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_NET_VALUE_DECL_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/net/value_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

template<
	typename Type,
	typename Policy
>
class value
{
	FCPPT_NONCOPYABLE(
		value
	);
public:
	explicit
	value(
		sanguis::diff_clock const &
	);

	~value();

	bool
	update();

	void
	set(
		Type
	);

	void
	reset();
private:
	void
	restart_timer();

	sanguis::diff_timer timer_;

	typedef
	fcppt::optional<
		Type
	>
	optional_type;

	optional_type old_;
};

}
}
}

#endif
