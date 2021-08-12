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

//! VTK variables and functions

// declares the renderer
vtkRenderer* renderer;

//declares the render window
vtkRenderWindow* window;

//declares the interactor
vtkRenderWindowInteractor* interactor;

//! HD variables and functions





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