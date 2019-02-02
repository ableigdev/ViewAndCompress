#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <QDialog>
#include <QMouseEvent>
#include <QWheelEvent>
#include <Qt3DExtras/Qt3DExtras>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/Qt3DRender>
#include <Qt3DCore/Qt3DCore>
#include <QVector3D>
#include <QPoint>
#include <QMatrix4x4>
#include <memory>
#include <string>
#include <memory>

class Viewer3D : public QDialog
{
    Q_OBJECT
public:
    explicit Viewer3D(QDialog* parent = nullptr);
    void show(const std::string& path);

private:
    bool eventFilter(QObject* object, QEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    std::unique_ptr<Qt3DExtras::Qt3DWindow> m_View;
    std::shared_ptr<Qt3DCore::QEntity> m_RootEntity;
    std::unique_ptr<Qt3DCore::QEntity> m_FlyingWedge;
    std::unique_ptr<Qt3DRender::QMaterial> m_Material;
    std::unique_ptr<Qt3DRender::QMesh> m_FlyingWedgeMesh;
    std::unique_ptr<Qt3DCore::QTransform> m_FlyingWedgeTransform;
    std::unique_ptr<Qt3DRender::QFrontFace> m_FrontFace;
    QPoint m_MoveStartPoint;
    QMatrix4x4 m_CameraMatrix;
};

#endif // VIEWER3D_H
