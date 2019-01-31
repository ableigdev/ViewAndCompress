#ifndef VIEWERIMPL_H
#define VIEWERIMPL_H

#include <QDialog>
#include "interfaces/IViewer.h"

namespace Ui
{
    class ViewerImpl;
}

class ViewerImpl : public interfaces::IViewer
{
    Q_OBJECT
public:
    ViewerImpl();
    virtual ~ViewerImpl();

    virtual int getCompressionLevel() const;
    virtual int getQuantizationBits() const;
    virtual std::string getPathToSourceFile() const;
    virtual std::string getPathToOutputFile() const;

private:
    Ui::ViewerImpl* m_UI;
    int m_CompressioLevel;
    int m_QuantizatioBits;
    std::string m_PathToSourceFile {};
    std::string m_PathToOutputFile {};
};


#endif // VIEWERIMPL_H
