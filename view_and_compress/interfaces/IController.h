#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QObject>

namespace interfaces
{
    class IController : public QObject
    {
        Q_OBJECT
    public:
        explicit IController(QObject* ptr = nullptr) : QObject(ptr) {}
        virtual ~IController() = default;
        virtual void show() = 0;

    public slots:
        virtual void catchCompressionAction() = 0;
        virtual void catchDecompressionAction() = 0;
    };
}

#endif // ICONTROLLER_H
