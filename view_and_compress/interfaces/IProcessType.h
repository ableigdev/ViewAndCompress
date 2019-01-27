#ifndef VIEW_AND_COMPRESS_IPROCESSTYPE_H
#define VIEW_AND_COMPRESS_IPROCESSTYPE_H

namespace interfaces
{
    class IProcessType
    {
    public:
        IProcessType() = default;
        virtual ~IProcessType() = default;
        virtual setCompressionLevel(int level) = 0;
        virtual setQuantizationBits(int quantizationBits) = 0;
    };
}

#endif //VIEW_AND_COMPRESS_IPROCESSTYPE_H
