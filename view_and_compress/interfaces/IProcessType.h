#ifndef VIEW_AND_COMPRESS_IPROCESSTYPE_H
#define VIEW_AND_COMPRESS_IPROCESSTYPE_H

#include <string>
#include "IProcessAction.h"

namespace interfaces
{
    class IProcessType
    {
    public:
        IProcessType() = default;
        virtual ~IProcessType() = default;
        virtual void setCompressionLevel(int level) = 0;
        virtual void setQuantizationBits(int quantizationBits) = 0;
        virtual void setPathToSourceFile(const std::string& path) = 0;
        virtual void setPathToOutputFile(const std::string& path) = 0;
        virtual void setProcessAction(IProcessAction* processAction) = 0;
    };
}

#endif //VIEW_AND_COMPRESS_IPROCESSTYPE_H
