#include <iostream>
#include "TetMesh.h"
#include "TriMesh.h"

// INCLUDE VTK LIBRARIES
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>

// INCLUDE HD LIBRARIES
#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>

// INCLUDE IGL
#include <igl/opengl/glfw/Viewer.h>
#include <igl/readOBJ.h>

//------------------------------------------------------------------------------
// DECLARED VARIABLES
//------------------------------------------------------------------------------

// the visualizer
igl::opengl::glfw::Viewer* viewer;

// the triangle mesh object
TriMesh* a_triMesh;

// the tetrahedral mesh object
TetMesh* a_tetMesh;

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
Eigen::Vector3d w_d;

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

// This function updates the collision detection
void updateCollision();

// This function updates the dynamics
void updateDynamics();

// This function updates the graphics
void updateGraphics();


int main(int argc, char* argv[])
{

    /*
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
    */

    // Initialize the haptic device
    initHD();

    // Initialize the graphics window
    initGraphics();

    while(HD_TRUE)
    {
        HDErrorInfo error;
        hdScheduleSynchronous(graphicsCallback, 0 , HD_DEFAULT_SCHEDULER_PRIORITY);

        if (HD_DEVICE_ERROR(error = hdGetError()))
        {
            hduPrintError(stderr, &error, "Failed to start the scheduler");
            break;
        }
    }

    // Close haptic device
    endHD();

    return EXIT_SUCCESS;
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
    // Imports the mesh
    a_triMesh->loadFromFileIGL("", viewer);

    // launch the viewer
    viewer->launch();

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
    hduVector3Dd velocity;
    HDdouble rotation[16];
    HDdouble rotation_velocity[3];

    hduVector3Dd force = { 0, 0, 0 };

    hdBeginFrame(ghHD);

    hdGetDoublev(HD_CURRENT_POSITION, position);
    pos.x() = position[0]; pos.y() = position[1]; pos.z() = position[2];
    hdGetDoublev(HD_CURRENT_VELOCITY, velocity);
    vel.x() = velocity[0]; vel.y() = velocity[1]; vel.z() = velocity[2];
    hdGetDoublev(HD_CURRENT_TRANSFORM, rotation);
    w(0,0) = rotation[0]; w(0 , 1) = rotation[1]; w (0, 2 ) = rotation[2]; w(0,3) = rotation[3];
    w(1,0) = rotation[4]; w(1 , 1) = rotation[5]; w (1, 2 ) = rotation[6]; w(1,3) = rotation[7];
    w(2,0) = rotation[8]; w(2 , 1) = rotation[9]; w (2, 2 ) = rotation[10]; w(2,3) = rotation[11];
    w(3,0) = rotation[12]; w(3 , 1) = rotation[13]; w (3, 2 ) = rotation[14]; w(3,3) = rotation[15];
    hdGetDoublev(HD_CURRENT_ANGULAR_VELOCITY, rotation_velocity);
    w_d.x() = rotation_velocity[0]; w_d.y() = rotation_velocity[1]; w_d.z() = rotation_velocity[2];
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
    // Functions for simulation
    updateCollision();
    updateDynamics();
    updateGraphics();

    return HD_CALLBACK_DONE;
}

//! Ends communication with the haptic device
void endHD()
{
    hdStopScheduler();
    hdUnschedule(hUpdateDeviceCallback);
    hdDisableDevice(ghHD);
}