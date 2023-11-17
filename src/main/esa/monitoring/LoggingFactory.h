#ifndef ESA_MONITORING_LOGGINGFACTORY_H_
#define ESA_MONITORING_LOGGINGFACTORY_H_

#include <esa/object/Object.h>

#include <memory>

namespace esa {
inline namespace v1_6 {
namespace monitoring {

class Logging;

class LoggingFactory : public object::Object {
public:
    virtual std::unique_ptr<Logging> createLogging() = 0;
};

} /* namespace monitoring */
} /* inline namespace v1_6 */
} /* namespace esa */

#endif /* ESA_MONITORING_LOGGINGFACTORY_H_ */
