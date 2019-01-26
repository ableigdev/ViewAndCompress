#include <QApplication>
#include <QLockFile>
#include <QDir>
#include <QMessageBox>
#include "draco/compression/encode.h"
#include "draco/core/cycle_timer.h"
#include "draco/io/mesh_io.h"
#include "draco/io/point_cloud_io.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLockFile lockFile(QDir::temp().absoluteFilePath("temp.lock"));

    if (!lockFile.tryLock(100))
    {
        QMessageBox message;
        message.setIcon(QMessageBox::Warning);
        message.setText("The application was run.\nYou can run only one instance of the application.");
        message.exec();
        return 1;
    }

    draco::EncoderBuffer buffer;
    return a.exec();
}
