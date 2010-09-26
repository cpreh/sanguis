#ifndef SANGUIS_CLIENT_PERK_CHOOSER_ACTIVATION_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CHOOSER_ACTIVATION_HPP_INCLUDED

#include "perk_chooser_fwd.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{

class perk_chooser_activation
{
	FCPPT_NONCOPYABLE(perk_chooser_activation)
public:
	explicit perk_chooser_activation(
		client::perk_chooser &
	);

	~perk_chooser_activation();
private:
	client::perk_chooser &instance_;
};

}
}

#endif
