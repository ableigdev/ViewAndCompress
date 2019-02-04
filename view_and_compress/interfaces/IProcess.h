#ifndef VIEW_AND_COMPRESS_IPROCESS_H
#define VIEW_AND_COMPRESS_IPROCESS_H

#include <string>
#include "IProcessAction.h"

namespace interfaces
{
    class IProcess
    {
    public:
        IProcess() = default;
        virtual ~IProcess() = default;
        virtual void setCompressionLevel(int level) = 0;
        virtual void setQuantizationBits(int quantizationBits) = 0;
        virtual void setPathToSourceFile(const std::string& path) = 0;
        virtual void setPathToOutputFile(const std::string& path) = 0;
        virtual std::string doProcessAction(IProcessAction* processAction) = 0;
    };
}

#endif //VIEW_AND_COMPRESS_IPROCESS_H
