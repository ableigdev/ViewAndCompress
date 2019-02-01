#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QIntValidator>
#include <QMessageBox>
#include <regex>
#include "ViewerImpl.h"
#include "ui_ViewerImpl.h"

ViewerImpl::ViewerImpl()
    : m_UI(new Ui::ViewerImpl),
      m_CompressioLevel(0),
      m_QuantizatioBits(0)
{
    m_UI->setupUi(this);
    m_UI->LineEdit_CompressionLevel->setValidator(new QIntValidator(1, 10, this));
    m_UI->LineEdit_QuantizationBits->setValidator(new QIntValidator(1, 30, this));
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

void ViewerImpl::on_Button_OpenFIle_clicked()
{
    std::string extension(".drc");
    std::regex rule(R"(.+()" + extension + R"()$)");
    std::cmatch result;
    QString filters("3D Models Files (*.ply *.drc)");
    QString name = QFileDialog::getOpenFileName(this,
                                 "Choose File",
                                 QDir::currentPath().toStdString().c_str(),
                                 filters);
    if (!name.isEmpty())
    {
        m_PathToSourceFile = name.toStdString();
        bool isFirstFileDrc = false;
        filters = "*.drc";
        if (std::regex_search(name.toStdString().c_str(), result, rule))
        {
            isFirstFileDrc = true;
            filters = "*.ply";
            extension = ".ply";
            rule = R"(.+()" + extension + R"()$)";
        }
        name = QFileDialog::getSaveFileName(this,
                                            "Save file",
                                            QDir::currentPath().toStdString().c_str(),
                                            filters);
        if (!name.isEmpty())
        {
            if (!std::regex_search(name.toStdString().c_str(), result, rule))
            {
                name += extension.c_str();
            }
            m_PathToOutputFile = name.toStdString();

            m_UI->GroupBox_EnterValues->setEnabled(!isFirstFileDrc);
            isFirstFileDrc ? m_UI->Button_CompressOrDecompress->setText("&Decompress") : m_UI->Button_CompressOrDecompress->setText("&Compress");
            m_UI->Button_CompressOrDecompress->setEnabled(true);
        }
    }
}

void ViewerImpl::on_Button_CompressOrDecompress_clicked()
{
    if (m_UI->Button_CompressOrDecompress->text() == "&Decompress")
    {
        emit doDecompress();
    }
    else
    {
        if (m_UI->LineEdit_CompressionLevel->text().isEmpty() &&
                m_UI->LineEdit_QuantizationBits->text().isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Enter data!");
        }
        else
        {
            m_CompressioLevel = m_UI->LineEdit_CompressionLevel->text().toInt();
            m_QuantizatioBits = m_UI->LineEdit_QuantizationBits->text().toInt();
            m_UI->LineEdit_CompressionLevel->setText("");
            m_UI->LineEdit_QuantizationBits->setText("");
            emit doCompress();
        }
    }
}

void ViewerImpl::message(const std::string& message)
{
    QMessageBox::information(this, "Result", message.c_str());
}
