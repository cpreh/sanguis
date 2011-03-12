#ifndef SANGUIS_MESSAGES_CALL_DISPATCHER_BASE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_DISPATCHER_BASE_HPP_INCLUDED

namespace sanguis
{
namespace messages
{
namespace call
{

template<
	typename Callee
>
class dispatcher_base
{
	FCPPT_NONCOPYABLE(
		dispatcher_base
	);
protected:
	dispatcher_base()
	{
	}
public:
	virtual typename Callee::result_type
	call(
		Callee &,
		base const &
	) const = 0;

	virtual ~dispatcher_base()
	{
	}
};

}
}
}

#endif
