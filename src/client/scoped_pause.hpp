#ifndef SANGUIS_CLIENT_SCOPED_PAUSE_HPP_INCLUDED
#define SANGUIS_CLIENT_SCOPED_PAUSE_HPP_INCLUDED

#include "send_callback.hpp"
#include <fcppt/function/object.hpp>
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
	explicit scoped_pause(
		client::send_callback const &
	);

	~scoped_pause();
private:
	client::send_callback const send_;
};

}
}

#endif
