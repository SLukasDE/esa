/*
MIT License
Copyright (c) 2019-2021 Sven Lukas

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

#ifndef ESL_DATABASE_SQL_ENGINE_H_
#define ESL_DATABASE_SQL_ENGINE_H_

#include <esl/database/sql/Interface.h>
#include <esl/database/table/Interface.h>
#include <esl/object/Values.h>
#include <esl/module/Implementation.h>

#include <string>
#include <initializer_list>
#include <memory>

namespace esl {
namespace database {
namespace sql {

class Engine final : public Interface::Engine {
public:
	static module::Implementation& getDefault();

	Engine(std::initializer_list<std::pair<std::string, std::string>> settings,
			const std::string& implementation = getDefault().getImplementation());

	Engine(const object::Values<std::string>& settings = getDefault().getProperties(),
			const std::string& implementation = getDefault().getImplementation());

	void addTables(const std::string& id, std::unique_ptr<table::Interface::Tables> tables) override;
	std::unique_ptr<database::Interface::ConnectionFactory> createConnectionFactory() override;

private:
	std::unique_ptr<Interface::Engine> engine;
};

} /* namespace sql */
} /* namespace database */
} /* namespace esl */

#endif /* ESL_DATABASE_SQL_ENGINE_H_ */