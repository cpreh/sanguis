#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_BODY_HPP_INCLUDED

#include <sanguis/server/speed_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace ifaces
{

class with_body
{
	FCPPT_NONCOPYABLE(
		with_body
	);
protected:
	with_body();

	virtual
	void
	reset_speed(
		sanguis::server::speed const &
	) = 0;

	virtual
	sanguis::server::speed const
	body_speed() const = 0;

	virtual
	sanguis::server::speed const
	initial_speed() const;
public:
	virtual
	~with_body() = 0;
};

}
}
}
}

#endif
