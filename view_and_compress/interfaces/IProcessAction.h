#ifndef IPROCESSACTION_H
#define IPROCESSACTION_H

#include <string>

namespace interfaces
{
    class IProcessAction
    {
    public:
        IProcessAction() = default;
        virtual ~IProcessAction() = default;
        virtual void setCompressionLevel(int level) = 0;
        virtual void setQuantizationBits(int quantizationBits) = 0;
        virtual void setPathToSourceFile(const std::string& path) = 0;
        virtual void setPathToOutputFile(const std::string& path) = 0;
        virtual std::string doAction() = 0;
    };
}

#endif // IPROCESSACTION_H
