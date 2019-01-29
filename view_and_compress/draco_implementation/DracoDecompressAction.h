#ifndef DRACODECOMPRESSACTION_H
#define DRACODECOMPRESSACTION_H

#include <vector>
#include <memory>
#include "interfaces/IProcessAction.h"
#include "draco/compression/decode.h"

namespace draco_impl
{
    class DracoDecompressAction : public interfaces::IProcessAction
    {
    public:
        DracoDecompressAction();
        virtual ~DracoDecompressAction() = default;
        virtual void setCompressionLevel(int level);
        virtual void setQuantizationBits(int quantizationBits);
        virtual void setPathToSourceFile(const std::string& path);
        virtual void setPathToOutputFile(const std::string& path);
        virtual std::string doAction();

    private:
        void readFromFile();
        std::string returnError(const draco::Status& status);

    private:
        int m_QuantizationBits;
        int m_CompressionLevel;
        std::unique_ptr<draco::PointCloud> m_PointCloud;
        std::string m_PathToSourceFile {};
        std::string m_PathToOutputFile {};
        std::vector<char> m_DataFromFile {};
    };
}

#endif // DRACODECOMPRESSACTION_H
