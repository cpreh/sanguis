#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "value.hpp"
#include "constant.hpp"
#include "linear.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	)
public:
	typedef property::value value_type;

	typedef property::constant constant_type;

	typedef property::linear linear_type;

	explicit base(
		value_type
	);

	constant_type const
	constant();

	linear_type const
	linear();
	
	void
	constant(
		constant_type const &
	);

	void
	linear(
		linear_type const &
	);
protected:
	virtual ~base();
private:
	void
	recalc_max();

	virtual void
	on_recalc_max(
		value_type
	) = 0;

	value_type const base_;

	constant_type constant_;

	linear_type linear_;
};

}
}
}
}

#endif
