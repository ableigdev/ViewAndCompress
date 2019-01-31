#ifndef IVIEWER_H
#define IVIEWER_H

#include <QDialog>
#include <string>

namespace interfaces
{
    class IViewer : public QDialog
    {
        Q_OBJECT
    public:
        explicit IViewer(QDialog* ptr = nullptr) : QDialog(ptr) {}
        virtual ~IViewer() = default;

        virtual int getCompressionLevel() const = 0;
        virtual int getQuantizationBits() const = 0;
        virtual std::string getPathToSourceFile() const = 0;
        virtual std::string getPathToOutputFile() const = 0;

    signals:
        void doCompress();
        void doDecompress();
    };
}

#endif // IVIEWER_H
