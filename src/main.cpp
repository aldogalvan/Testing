#include <stdio.h>
#include <iostream>


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

//! IGL Viewer
igl::opengl::glfw::Viewer viewer;

//! Tool variables
Eigen::Vector3d toolPos0;
Eigen::Vector3d toolPos;
Eigen::Vector3d toolVel;
int toolRadius = 1;

//! Object variables
Eigen::MatrixX3d V_;
Eigen::MatrixX3d V_0;
Eigen::MatrixX3i F_;
Eigen::MatrixX3d TV_;
Eigen::MatrixX3d TV_0;
Eigen::MatrixX2i TL_;
Eigen::MatrixX3i TF_;
Eigen::MatrixX4i TT_;

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

// This function updates the graphics
void updateGraphics();


int main(int argc, char* argv[])
{

    // Initialize the haptic device
    // initHD();

    // Initialize the graphics window
    // initGraphics();

    // Load the mesh
    igl::readOBJ("/home/herolab/CLionProjects/Testing/assets/spot_triangulated.obj", V_, F_);

    // Plot the mesh
    viewer.data().set_mesh(V_, F_);
    viewer.core().is_animating = true;
    viewer.launch();


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

//------------------------------------------------------------------------------
// HD COMMUNICATION
//------------------------------------------------------------------------------

//! Initializes communication with the haptic device
void initHD()
{
    HDErrorInfo error;
    ghHD = hdInitDevice(HD_DEFAULT_DEVICE);
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        hduPrintError(stderr, &error, "Failed to initialize haptic device");
        fprintf(stderr, "\nPress any key to quit.\n");
        getchar();
        exit(-1);
    }


    hdEnable(HD_FORCE_OUTPUT);

    hUpdateDeviceCallback = hdScheduleAsynchronous(
            hapticsCallback, 0, HD_MAX_SCHEDULER_PRIORITY);

    hdStartScheduler();
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        hduPrintError(stderr, &error, "Failed to start the scheduler");
        exit(-1);
    }

}


//! Main haptics callback function
HDCallbackCode HDCALLBACK hapticsCallback(void *pUserData)
{

    HDErrorInfo error;
    hduVector3Dd pos;
    hduVector3Dd vel;

    hduVector3Dd force = { 0, 0, 0 };

    hdBeginFrame(ghHD);

    hdGetDoublev(HD_CURRENT_POSITION, pos);
    toolPos.x() = pos[0]; toolPos.y() = pos[1]; toolPos.z() = pos[2];
    hdGetDoublev(HD_CURRENT_VELOCITY, vel);
    toolVel.x() = vel[0]; toolVel.y() = vel[1]; toolVel.z() = vel[2];

    hdSetDoublev(HD_CURRENT_FORCE, force);

    hdEndFrame(ghHD);

    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
         /*This is likely a more serious error, so bail.*/
        hduPrintError(stderr, &error, "Error during haptic rendering");
        exit(-1);
    }

    return HD_CALLBACK_CONTINUE;
}

//! Low priority graphics callback
HDCallbackCode HDCALLBACK graphicsCallback(void *pUserData)
{

    viewer.data().set_points(toolPos, Eigen::RowVector3d (1 , 1, 1));

    return HD_CALLBACK_DONE;
}

//! Ends communication with the haptic device
void endHD()
{
    hdStopScheduler();
    hdUnschedule(hUpdateDeviceCallback);
    hdDisableDevice(ghHD);
}

