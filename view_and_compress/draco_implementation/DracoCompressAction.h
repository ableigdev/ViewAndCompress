#ifndef DRACOCOMPRESSACTION_H
#define DRACOCOMPRESSACTION_H

#include <memory>
#include "interfaces/IProcessAction.h"
#include "draco/io/mesh_io.h"
#include "draco/compression/encode.h"

namespace draco_impl
{
    class DracoCompressAction : public interfaces::IProcessAction
    {
    public:
        DracoCompressAction();
        virtual ~DracoCompressAction() = default;
        virtual void setCompressionLevel(int level);
        virtual void setQuantizationBits(int quantizationBits);
        virtual void setPathToSourceFile(const std::string& path);
        virtual void setPathToOutputFile(const std::string& path);
        virtual std::string doAction();

    private:
        std::string encodeMeshToFile(const draco::Mesh& mesh, draco::Encoder* encoder);

    private:
        int m_QuantizationBits;
        int m_CompressionLevel;
        std::unique_ptr<draco::PointCloud> m_PointCloud;
        std::string m_PathToSourceFile {};
        std::string m_PathToOutputFile {};
        const int m_TexCoordsQuantizationBits = 12;
        const int m_NormalsQuantizationBits = 10;
        const int m_GenericQuantizationBits = 8;
    };
}

#endif // DRACOCOMPRESSACTION_H
