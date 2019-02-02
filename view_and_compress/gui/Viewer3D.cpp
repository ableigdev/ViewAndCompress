#include "Viewer3D.h"

Viewer3D::Viewer3D(QDialog* parent)
    : QDialog (parent),
      m_View(new Qt3DExtras::Qt3DWindow),
      m_RootEntity(new Qt3DCore::QEntity),
      m_FlyingWedge(new Qt3DCore::QEntity),
      m_Material(new Qt3DExtras::QMetalRoughMaterial),
      m_FlyingWedgeMesh(new Qt3DRender::QMesh),
      m_FlyingWedgeTransform(new Qt3DCore::QTransform),
      m_FrontFace(new Qt3DRender::QFrontFace)
{
    m_View->installEventFilter(this);
    m_MoveStartPoint.setX(-1);
}

void Viewer3D::show(const std::string& path)
{
    QUrl data = QUrl::fromLocalFile(path.c_str());
    m_FlyingWedge->setParent(m_RootEntity.get());
    m_Material->setParent(m_RootEntity.get());
    m_FrontFace->setParent(m_RootEntity.get());
    m_FlyingWedgeMesh->setSource(data);
    m_FlyingWedgeTransform->setScale3D(QVector3D(50, 50, 50));
    m_FrontFace->setDirection(Qt3DRender::QFrontFace::CounterClockWise);
    m_FlyingWedge->addComponent(m_FlyingWedgeMesh.get());
    m_FlyingWedge->addComponent(m_Material.get());
    m_FlyingWedge->addComponent(m_FlyingWedgeTransform.get());
    Qt3DRender::QCamera* camera = m_View->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setUpVector(QVector3D(0, 1, 0));
    camera->setViewCenter(QVector3D(0, 0, 0));
    camera->transform()->setScale(1.f);
    m_View->setRootEntity(m_RootEntity.get());
    m_View->show();
}

bool Viewer3D::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::Wheel)
    {
        wheelEvent(dynamic_cast<QWheelEvent*>(event));
        return true;
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        mousePressEvent(dynamic_cast<QMouseEvent*>(event));
        return true;
    }
    else if (event->type() == QEvent::MouseMove)
    {
        mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
        return true;
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        mouseReleaseEvent(dynamic_cast<QMouseEvent*>(event));
        return true;
    }

    return QObject::eventFilter(object, event);
}

void Viewer3D::mouseMoveEvent(QMouseEvent *event)
{
    if (m_MoveStartPoint.x() > -1)
    {
        QPoint delta = event->pos() - m_MoveStartPoint;
        float angle = static_cast<float>(QPoint::dotProduct(delta, delta)) / 100.f;
        QVector3D axis = QVector3D(delta.y(), delta.x(), 0);
        QMatrix4x4 rotationMatrix = Qt3DCore::QTransform::rotateAround(-m_View->camera()->position(), angle, axis);
        QMatrix4x4 matrix = rotationMatrix * m_CameraMatrix;
        m_View->camera()->transform()->setMatrix(matrix);
    }
}

void Viewer3D::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_MoveStartPoint = event->pos();
        m_CameraMatrix = m_View->camera()->transform()->matrix();
    }
}

void Viewer3D::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (m_MoveStartPoint.x() > 1)
    {
        m_MoveStartPoint.setX(-1);
        m_CameraMatrix = m_View->camera()->transform()->matrix();
    }
}

void Viewer3D::wheelEvent(QWheelEvent *event)
{
    Qt3DCore::QTransform* transform = m_View->camera()->transform();
    float scale = transform->scale();
    QPoint delta = event->angleDelta();
    float zoomDistance = scale * static_cast<float>(delta.y()) / 500.f;
    scale -= zoomDistance;
    scale = std::min(10.000f, scale);
    scale = std::max(0.001f, scale);
    transform->setScale(scale);
}
