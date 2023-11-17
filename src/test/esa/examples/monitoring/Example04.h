#ifndef ESA_EXAMPLES_LOGGING_EXAMPLE04_H_
#define ESA_EXAMPLES_LOGGING_EXAMPLE04_H_

#include <esa/examples/Logger.h>

namespace esa {
inline namespace v1_6 {
namespace examples {
namespace logging {

class Example04 {
public:
	Example04() = default;
	~Example04() = default;

	float divide(float a, float b);
};

void example04();

} /* namespace logging */
} /* namespace examples */
} /* inline namespace v1_6 */
} /* namespace esa */

#endif /* ESA_EXAMPLES_LOGGING_EXAMPLE04_H_ */
