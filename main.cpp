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

// Close the haptic device
void endHD();

// Update the force callback
HDCallbackCode HDCALLBACK hapticsCallback(void *pUserData);

// Update the graphics callback
HDCallbackCode HDCALLBACK graphicsCallback(void *pUserData);

//------------------------------------------------------------------------------
// DECLARED FUNCTIONS
//------------------------------------------------------------------------------

// This function initializes the graphics
void initGraphics();

// This function updates the graphics
void updateGraphics();

// This function closes all graphics
void endGraphics();

// This is the main haptic and graphic rendering loop
void mainLoop();

int main(int argc, char* argv[])
{
    // Create the volumetric mesh and load file
    my_mesh = new TetMesh();
    my_mesh->loadFromFileVTU("/home/aldo/CLionProjects/Testing/assets/volumetric_mesh.vtu");

    // starts the graphic renderer
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

    // Initialize the haptic device
    initHD();

    // start the main loop
    mainLoop();

    // Close haptic device
    endHD();

    return EXIT_SUCCESS;
}

void mainLoop()
{

}

void updateCollision(void)
{

}

void updateDynamics(void)
{

}

//------------------------------------------------------------------------------
// GRAPHIC RENDERING
//------------------------------------------------------------------------------

//! Initializes the graphics
void initGraphics()
{

}

//! Updates the graphics
void updateGraphics()
{

}

//! Closes the graphics
void endGraphics()
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

    hdEnable(HD_FORCE_OUTPUT);
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
    HDErrorInfo error;
    hduVector3Dd position;
    hduVector3Dd force = { 0, 0, 0 };

    hdBeginFrame(ghHD);

    hdSetDoublev(HD_CURRENT_FORCE, force);

    hdEndFrame(ghHD);

    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        /* This is likely a more serious error, so bail. */
        hduPrintError(stderr, &error, "Error during haptic rendering");
        exit(-1);
    }

    return HD_CALLBACK_CONTINUE;
}

//! Low priority graphics callback
HDCallbackCode HDCALLBACK graphicsCallback(void *pUserData)
{
    HapticDisplayState *pState = (HapticDisplayState *) pUserData;
    HDErrorInfo error;
    int currentButtons;

    hdGetDoublev(HD_CURRENT_POSITION, pState->position);
    hdGetDoublev(HD_CURRENT_VELOCITY, pState->velocity);
    hdGetDoublev(HD_CURRENT_TRANSFORM, pState->rotation);
    hdGetDoublev(HD_CURRENT_ANGULAR_VELOCITY, pState->rotation_velocity);
    hdGetIntegerv(HD_CURRENT_BUTTONS, &currentButtons);

    if (currentButtons & HD_DEVICE_BUTTON_1 == 1){
        pState->button1Pressed = HD_TRUE;
    }
    else {
        pState->button1Pressed = HD_FALSE;
    }

    if (currentButtons & HD_DEVICE_BUTTON_2 == 1){
        pState->button2Pressed = HD_TRUE;
    }
    else {
        pState->button2Pressed = HD_FALSE;
    }

    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        /* This is likely a more serious error, so bail. */
        hduPrintError(stderr, &error, "Error during haptic rendering");
        exit(-1);
    }

    return HD_CALLBACK_DONE;
}

//! Ends communication with the haptic device
void endHD()
{

}