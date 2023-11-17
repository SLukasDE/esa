#ifndef ESA_EXAMPLES_LOGGING_EXAMPLE03_H_
#define ESA_EXAMPLES_LOGGING_EXAMPLE03_H_

#include <esa/logging/Logger.h>

namespace esa {
inline namespace v1_6 {
namespace examples {
namespace logging {

class Example03 {
public:
	Example03() = default;
	~Example03() = default;

	float divide(float a, float b);

private:
	static esl::monitoring::Logger<> logger;
};

void example03();

} /* namespace logging */
} /* namespace examples */
} /* inline namespace v1_6 */
} /* namespace esa */

#endif /* ESA_EXAMPLES_LOGGING_EXAMPLE03_H_ */
