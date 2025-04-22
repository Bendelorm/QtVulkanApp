#include "VulkanWindow.h"
#include "Renderer.h"
#include <QKeyEvent>

VulkanWindow::VulkanWindow()
{
}

QVulkanWindowRenderer* VulkanWindow::createRenderer()
{
    //Makes a new instance of the RenderWindow (our Renderer) class
    mRenderer = new Renderer(this, true); // last true == try MSAA

    //Camera is made when the renderer is made, so we know it is valid now
    //We set values on the camera a lot from this class, so it is convenient to have a pointer to it
    mCamera = &dynamic_cast<Renderer*>(mRenderer)->mCamera;

    return mRenderer;
}

void VulkanWindow::setCameraSpeed(float value)
{
    mCameraSpeed += value;

    //Keep within some min and max values
    if(mCameraSpeed < 0.01f)
        mCameraSpeed = 0.01f;
    if (mCameraSpeed > 0.3f)
        mCameraSpeed = 0.3f;
}

void VulkanWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_G)
    {
        //dynamic_cast<RenderWindow*>(mRenderWindow)->mObjects.at(mIndex)->move(-0.1f);
        if(mSelectedObject)
        {
            qDebug("Move object");
            mSelectedObject->move(-0.1f);
        }
    }
    if(event->key() == Qt::Key_F)
    {
        if (cameraOption == 0)
        {
            mCamera->cameraOffset = {0.0f, 3.0f, 10.0f};
            cameraOption = 1;
        }
        else if (cameraOption == 1)
        {
            mCamera->cameraOffset = {0.0f, 10.0f, 30.0f};
            cameraOption = 2;
        }
        else if (cameraOption == 2)
        {
            mCamera->cameraOffset = {0.0f, 20.0f, 10.0f};
            cameraOption = 0;
        }
    }
    if (event->key() == Qt::Key_Escape)
    {
        QCoreApplication::quit();       //Shuts down the whole program
    }

    if (event->key() == Qt::Key_0)
        mIndex = 0;
    if (event->key() == Qt::Key_1)
        mIndex = 1;

    if(event->key() == Qt::Key_R)
    {
        dynamic_cast<Renderer*>(mRenderer)->mCamera.rotate(45, 0.0f, 0.0f, 1.0f);
    }

    //    You get the keyboard input like this
    if(event->key() == Qt::Key_W)
    {
        mInput.W = true;
    }
    if(event->key() == Qt::Key_S)
    {
        mInput.S = true;
    }
    if(event->key() == Qt::Key_D)
    {
        mInput.D = true;
    }
    if(event->key() == Qt::Key_A)
    {
        mInput.A = true;
    }
    if(event->key() == Qt::Key_Q)
    {
        mInput.Q = true;
    }
    if(event->key() == Qt::Key_E)
    {
        mInput.E = true;
    }
    if(event->key() == Qt::Key_Z)
    {
    }
    if(event->key() == Qt::Key_X)
    {
    }
    if(event->key() == Qt::Key_Up)
    {
        mInput.UP = true;
    }
    if(event->key() == Qt::Key_Down)
    {
        mInput.DOWN = true;
    }
    if(event->key() == Qt::Key_Left)
    {
        mInput.LEFT = true;
    }
    if(event->key() == Qt::Key_Right)
    {
        mInput.RIGHT = true;
    }
}

void VulkanWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        mInput.W = false;
    }
    if(event->key() == Qt::Key_S)
    {
        mInput.S = false;
    }
    if(event->key() == Qt::Key_D)
    {
        mInput.D = false;
    }
    if(event->key() == Qt::Key_A)
    {
        mInput.A = false;
    }
    if(event->key() == Qt::Key_Q)
    {
        mInput.Q = false;
    }
    if(event->key() == Qt::Key_E)
    {
        mInput.E = false;
    }
    if(event->key() == Qt::Key_Z)
    {
    }
    if(event->key() == Qt::Key_X)
    {
    }
    if(event->key() == Qt::Key_Up)
    {
        mInput.UP = false;
    }
    if(event->key() == Qt::Key_Down)
    {
        mInput.DOWN = false;
    }
    if(event->key() == Qt::Key_Left)
    {
        mInput.LEFT = false;
    }
    if(event->key() == Qt::Key_Right)
    {
        mInput.RIGHT = false;
    }
}

void VulkanWindow::wheelEvent(QWheelEvent *event)
{
    //QWheelEvent gives an x and y value in a QPoint
    //Y == Vertical scroll, X = Horizontal scroll
    QPoint numDegrees = event->angleDelta();

    //if RMB, change the speed of the camera
    if (mInput.RMB)
    {
        if (numDegrees.y() < 1)
            setCameraSpeed(-0.002f);
        if (numDegrees.y() > 1)
            setCameraSpeed(0.002f);
    }
    qDebug("CameraSpeed: %f", mCameraSpeed);
}

void VulkanWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        mInput.RMB = true;
    if (event->button() == Qt::LeftButton)
        mInput.LMB = true;
    if (event->button() == Qt::MiddleButton)
        mInput.MMB = true;
}

void VulkanWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        mInput.RMB = false;
    if (event->button() == Qt::LeftButton)
        mInput.LMB = false;
    if (event->button() == Qt::MiddleButton)
        mInput.MMB = false;
}

void VulkanWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mInput.RMB)
    {
        mMouseXlast = event->pos().x() - mMouseXlast;
        mMouseYlast = event->pos().y() - mMouseYlast;

        float yawAmount = -mCameraRotateSpeed * mMouseXlast;
        float pitchAmount = -mCameraRotateSpeed * mMouseYlast;

        if (mMouseXlast != 0)
        {
            dynamic_cast<Renderer*>(mRenderer)->mCamera.yaw(yawAmount);

            // Also rotate player
            auto* player = dynamic_cast<Renderer*>(mRenderer)->mObjects.at(3);
            player->rotate(yawAmount, 0.f, 1.f, 0.f);
        }
        if (mMouseYlast != 0)
        {
            dynamic_cast<Renderer*>(mRenderer)->mCamera.pitch(pitchAmount);
        }
    }

    mMouseXlast = event->pos().x();
    mMouseYlast = event->pos().y();
}

void VulkanWindow::handleInput(float deltaTime)
{
    if (bCanMove)
    {
        auto* player = dynamic_cast<Renderer*>(mRenderer)->mObjects.at(3);
        QVector3D forward = player->getForward();  // Get the updated forward vector based on yaw
        QVector3D right = QVector3D::crossProduct(forward, QVector3D(0.f, 1.f, 0.f));  // Right vector

        // Move the player based on the updated direction
        if (mInput.W)
            player->move(-forward.x() * moveSpeed * deltaTime, 0.f, -forward.z() * moveSpeed * deltaTime);
        if (mInput.S)
            player->move(forward.x() * moveSpeed * deltaTime, 0.f, forward.z() * moveSpeed * deltaTime);
        if (mInput.D)
            player->move(-right.x() * moveSpeed * deltaTime, 0.f, -right.z() * moveSpeed * deltaTime);
        if (mInput.A)
            player->move(right.x() * moveSpeed * deltaTime, 0.f, right.z() * moveSpeed * deltaTime);
    }
}
