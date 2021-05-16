#include "Ares/Events/Event.h"
#include <ostream>
namespace Ares
{
	std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}