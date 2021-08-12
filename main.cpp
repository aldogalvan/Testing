#include <iostream>
#include "TetMesh.h"

// INCLUDE VTK LIBRARIES
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>

// INCLUDE HD LIBRARIES
#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>

//------------------------------------------------------------------------------
// DECLARED VARIABLES
//------------------------------------------------------------------------------

// the volumetric mesh model
TetMesh* my_mesh;

// tool position
Eigen::Vector3d pos;

// tool velocity
Eigen::Vector3d vel;

// tool acceleration
Eigen::Vector3d acc;

// tool rotation
Eigen::Matrix4d w;

// tool rotational velocity
Eigen::Matrix4d w_d;

// tool angular acceleration
Eigen::Matrix4d w_dd;

//! VTK variables and functions
// declares the renderer
vtkRenderer* renderer;

//declares the render window
vtkRenderWindow* window;

//declares the interactor
vtkRenderWindowInteractor* interactor;

//! HD variables and functions
static HHD ghHD = HD_INVALID_HANDLE;
static HDSchedulerHandle hUpdateDeviceCallback = HD_INVALID_HANDLE;

typedef struct
{
    hduVector3Dd position;
    hduVector3Dd velocity;
    HDdouble rotation[16];
    HDdouble rotation_velocity[3];
    HDboolean button1Pressed;
    HDboolean button2Pressed;
} HapticDisplayState;

// Initialize the haptic device
void initHD();

// Update the force callback
HDCallbackCode HDCALLBACK hapticsCallback(void *pUserData);

//------------------------------------------------------------------------------
// DECLARED FUNCTIONS
//------------------------------------------------------------------------------

// This function updates the graphics
void updateGraphics(void);

// This function updates the haptics
void updateHaptics(void);

// This function updates the collisions
void updateCollisions(void);

// This function updates the dynamics
void updateDynamics(void);

int main(int argc, char* argv[])
{
    //! Create the volumetric mesh and load file
    my_mesh = new TetMesh();
    my_mesh->loadFromFileVTU("/home/aldo/CLionProjects/Testing/assets/volumetric_mesh.vtu");

    //! starts the graphic renderer
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);

    //get the actor for all objects
    vtkSmartPointer<vtkActor> actor = my_mesh->getActor();
    renderer->AddActor(actor);

    // render the window
    renderWindow->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}

void updateCollision(void)
{

}

void updateDynamics(void)
{

}

void updateGraphics(void)
{

}

void updateHaptics(void)
{

}

//------------------------------------------------------------------------------
// HD COMMUNICATION
//------------------------------------------------------------------------------

//! Initializes communication with the haptic device
void initHD()
{
    HDErrorInfo error;
    ghHD = hdInitDevice(HD_DEFAULT_DEVICE);
    if(HD_DEVICE_ERROR(error = hdGetError()))
    {
        hduPrintError(stderr, &error, "Failed to initialize haptic device");
        fprintf(stderr, "\nPress any key to quit.\n");
        getchar();
        exit(-1);
    }

    hUpdateDeviceCallback = hdScheduleAsynchronous(
            hapticsCallback, 0, HD_MAX_SCHEDULER_PRIORITY
            );

    hdStartScheduler();
    if(HD_DEVICE_ERROR(error = hdGetError()))
    {
        hduPrintError(stderr, &error, "Failed to start the scheduler");
        exit(-1);
    }
}

//! Main haptics callback function
HDCallbackCode HDCALLBACK hapticsCallback(void *pUserData)
{
    hduVector3Dd position;
    hduVector3Dd velocity;
    HDErrorInfo error;

    hdBeginFrame(ghHD);

    hdGetDoublev(HD_CURRENT_POSITION, position);
    hdGetDoublev(HD_CURRENT_VELOCITY, velocity);
}