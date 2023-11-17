/*
MIT License
Copyright (c) 2019-2023 Sven Lukas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ESA_OBJECT_BEAN_H_
#define ESA_OBJECT_BEAN_H_

#include <esa/object/Object.h>

#include <string>
#include <vector>

namespace esa {
inline namespace v1_6 {
namespace object {

class IBean : public virtual Object {
public:
	virtual std::set<std::string> getBeanProperties() const = 0;
	virtual Object* getBeanProperty(const std::string& id) const = 0;
	virtual void setBeanProperty(const std::string& id, Object* object) const = 0;
};

} /* namespace object */
} /* inline namespace v1_6 */
} /* namespace esa */

#endif /* ESA_OBJECT_BEAN_H_ */
