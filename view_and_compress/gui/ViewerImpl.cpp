#include "ViewerImpl.h"
#include "ui_ViewerImpl.h"

ViewerImpl::ViewerImpl()
    : m_UI(new Ui::ViewerImpl),
      m_CompressioLevel(0),
      m_QuantizatioBits(0)
{
    m_UI->setupUi(this);
}

ViewerImpl::~ViewerImpl()
{
    delete m_UI;
}

int ViewerImpl::getCompressionLevel() const
{
    return m_CompressioLevel;
}

int ViewerImpl::getQuantizationBits() const
{
    return m_QuantizatioBits;
}

std::string ViewerImpl::getPathToSourceFile() const
{
    return m_PathToSourceFile;
}

std::string ViewerImpl::getPathToOutputFile() const
{
    return m_PathToOutputFile;
}
