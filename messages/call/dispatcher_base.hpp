#ifndef SANGUIS_MESSAGES_CALL_DISPATCHER_BASE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_DISPATCHER_BASE_HPP_INCLUDED

namespace sanguis
{
namespace messages
{

template<
	typename Callee
>
class call_dispatcher_base {
	SGE_NONCOPYABLE(call_dispatcher_base)
protected:
	call_dispatcher_base()
	{}
public:
	virtual typename Calle::result_type
	call(
		Calle &,
		base const &
	) const = 0;

	virtual ~call_dispatcher_base()
	{}
};

}
}

#endif
