#include <esa/examples/logging/Example01.h>
#include <esa/logging/Logger.h>

namespace esa {
inline namespace v1_6 {
namespace examples {
namespace logging {

void example01() {
	/* creating a logger class */
	esl::monitoring::Logger<> logger;

	/* That's it, now you can use it already */
	logger.info << "Hello world!" << std::endl;

	/* Ups, you see nothing.
	 * We have not "initialized" the logging framework.
	 * Let's go to logger example 2 to see how to initialize... */
}

} /* namespace logging */
} /* namespace examples */
} /* inline namespace v1_6 */
} /* namespace esa */
