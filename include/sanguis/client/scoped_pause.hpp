#ifndef SANGUIS_CLIENT_SCOPED_PAUSE_HPP_INCLUDED
#define SANGUIS_CLIENT_SCOPED_PAUSE_HPP_INCLUDED

#include <sanguis/client/send_callback.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{

class scoped_pause
{
	FCPPT_NONCOPYABLE(
		scoped_pause
	);
public:
	explicit
	scoped_pause(
		sanguis::client::send_callback const &
	);

	~scoped_pause();
private:
	sanguis::client::send_callback const send_;
};

}
}

#endif
