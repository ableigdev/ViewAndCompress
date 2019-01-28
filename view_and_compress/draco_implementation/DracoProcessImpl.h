#ifndef VIEW_AND_COMPRESS_DRACOPROCESSIMPL_H
#define VIEW_AND_COMPRESS_DRACOPROCESSIMPL_H

#include <memory>
#include "DracoProcessTypeImpl.h"
#include "interfaces/IProcess.h"

namespace draco_impl
{
    class DracoProcessImpl : public interfaces::IProcess
    {
    public:
        DracoProcessImpl();
        virtual ~DracoProcessImpl() = default;
        virtual void setCompressionLevel(int level);
        virtual void setQuantizationBits(int quantizationBits);
        virtual void setPathToSourceFile(const std::string& path);
        virtual void setPathToOutputFile(const std::string& path);
        virtual void setProcessAction(interfaces::IProcessAction* processAction);

    private:
        std::unique_ptr<DracoProcessTypeImpl> m_DracoProcessTypeImpl;
    };
}

#endif // VIEW_AND_COMPRESS_DRACOPROCESSIMPL_H
