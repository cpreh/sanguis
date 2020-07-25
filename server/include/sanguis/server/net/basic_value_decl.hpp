#ifndef SANGUIS_SERVER_NET_BASIC_VALUE_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_NET_BASIC_VALUE_DECL_HPP_INCLUDED

#include <sanguis/server/net/basic_value_fwd.hpp>
#include <sge/timer/basic_decl.hpp>
#include <sge/timer/clocks/parameter_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

template<
	typename Type,
	typename Policy,
	typename Clock
>
class basic_value
{
	FCPPT_NONCOPYABLE(
		basic_value
	);
public:
	explicit
	basic_value(
		sge::timer::clocks::parameter<
			Clock
		>
	);

	~basic_value();

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

	typedef
	sge::timer::basic<
		Clock
	>
	timer;

	timer timer_;

	typedef
	fcppt::optional::object<
		Type
	>
	optional_type;

	optional_type old_;
};

}
}
}

#endif
