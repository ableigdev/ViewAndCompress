#ifndef VIEW_AND_COMPRESS_IPROCESS_H
#define VIEW_AND_COMPRESS_IPROCESS_H

namespace interfaces
{
    class IProcess
    {
    public:
        IProcess() = default;
        virtual ~IProcess() = default;
        virtual setCompressionLevel(int level) = 0;
        virtual setQuantizationBits(int quantizationBits) = 0;
    };
}

#endif //VIEW_AND_COMPRESS_IPROCESS_H
