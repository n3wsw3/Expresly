#include <string>
#include <utility>

namespace expresly {
    class expression {
        public:
            expression(const std::string& exp) : original{exp} {}
            expression(std::string&& exp) : original{std::move(exp)} {}
        private:
            std::string original;
    };
}