#ifndef SANGUIS_SERVER_NET_BASIC_VALUE_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_NET_BASIC_VALUE_DECL_HPP_INCLUDED

#include <sanguis/server/net/basic_value_fwd.hpp>
#include <sge/timer/basic_decl.hpp>
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
		Clock const &
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
