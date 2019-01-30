#ifndef DRACOPROCESSTYPEIMPL_H
#define DRACOPROCESSTYPEIMPL_H

#include "interfaces/IProcessType.h"
#include "interfaces/IProcessAction.h"

namespace draco_impl
{
    class DracoProcessTypeImpl : public interfaces::IProcessType
    {
    public:
        DracoProcessTypeImpl();
        virtual ~DracoProcessTypeImpl() = default;
        virtual void setCompressionLevel(int level);
        virtual void setQuantizationBits(int quantizationBits);
        virtual void setPathToSourceFile(const std::string& path);
        virtual void setPathToOutputFile(const std::string& path);
        virtual std::string doProcessAction(interfaces::IProcessAction* processAction);

    private:
        int m_CompressionLevel;
        int m_QuantizationBits;
        std::string m_PathToSourceFile {};
        std::string m_PathToOutputFile {};
    };
}

#endif // DRACOPROCESSTYPEIMPL_H
