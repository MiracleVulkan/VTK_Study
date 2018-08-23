/*=========================================================================

Program:   Visualization Toolkit
Module:    Cylinder.cxx

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This simple example shows how to do basic rendering and pipeline
// creation using C++.
//
#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkLight.h"
#include "vtkCamera.h"
#include "vtkPolyDataWriter.h"
#include <vtkLine.h>
#include "vtkFloatArray.h"
#include "vtkTriangle.h"
#include "vtkUnstructuredGrid.h"
#include "vtkPointData.h"

int main()
{

	//创建一个圆柱体，并添加相机和灯光
#if 0

	// This creates a polygonal cylinder model with eight circumferential facets.
	//
	vtkCylinderSource *cylinder = vtkCylinderSource::New();
	cylinder->SetResolution(18);
	double cylinderCenter[3] = { 0.0,0.0,0.0 };
	cylinder->SetCenter(cylinderCenter);

	// The mapper is responsible for pushing the geometry into the graphics
	// library. It may also do color mapping, if scalars or other attributes
	// are defined.
	//
	vtkPolyDataMapper *cylinderMapper = vtkPolyDataMapper::New();
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

	// The actor is a grouping mechanism: besides the geometry (mapper), it
	// also has a property, transformation matrix, and/or texture map.
	// Here we set its color and rotate it -22.5 degrees.
	vtkActor *cylinderActor = vtkActor::New();
	cylinderActor->SetMapper(cylinderMapper);
	cylinderActor->GetProperty()->SetColor(1.0, 1.0, 1.0);

	// Create the graphics structure. The renderer renders into the
	// render window. The render window interactor captures mouse events
	// and will perform appropriate camera or actor manipulation
	// depending on the nature of the events.
	//
	vtkRenderer *ren1 = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	vtkInteractorStyleTrackballCamera *style = vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);

	// Add the actors to the renderer, set the background and size
	//
	ren1->AddActor(cylinderActor);
	ren1->SetBackground(0.9, 0.9, 0.9);
	renWin->SetSize(800, 600);

	// We'll zoom in a little by accessing the camera and invoking a "Zoom"
	// method on it.
	ren1->ResetCamera();
	ren1->GetActiveCamera()->Zoom(1.5);
	renWin->Render();

	vtkLight* light1 = vtkLight::New();
	double color1[3] = { 0.0,0.0,1.0 };
	light1->SetColor(color1);
	float lightPosition1[3] = { 0.0,1.0,0.0 };
	light1->SetPosition(lightPosition1);
	ren1->AddLight(light1);

	vtkLight* light2 = vtkLight::New();
	double color2[3] = { 1.0,0.0,0.0 };
	light2->SetColor(color2);
	light2->SetSwitch(1);
	float lightPosition2[3] = { 0.0,1.0,1.0 };
	light2->SetPosition(lightPosition2);
	ren1->AddLight(light2);

	vtkCamera* myCamera = vtkCamera::New();
	double clippingRange[2] = { 0.01,20 };
	myCamera->SetClippingRange(clippingRange);
	myCamera->SetFocalPoint(0.0, 0.0, 0.0);
	myCamera->SetPosition(0.0, 0.0, 17.0);
	myCamera->SetViewUp(0.0, 1.0, 0.0);
	ren1->SetActiveCamera(myCamera);

	iren->Initialize();
	// This starts the event loop and as a side effect causes an initial render.
	iren->Start();

	// Exiting from here, we have to delete all the instances that
	// have been created.
	cylinder->Delete();
	cylinderMapper->Delete();
	cylinderActor->Delete();
	ren1->Delete();
	renWin->Delete();
	iren->Delete();
#endif

	//创建点的数据
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	points->SetNumberOfPoints(3);
	points->InsertPoint(0, 1.0, 0.0, 0.0);
	points->InsertPoint(1, 0.0, 0.0, 0.0);
	points->InsertPoint(2, 0.0, 1.0, 0.0);


	//属性数据
	vtkSmartPointer<vtkFloatArray> triangleScalars = vtkSmartPointer<vtkFloatArray>::New();
	triangleScalars->SetNumberOfTuples(3);
	triangleScalars->InsertValue(0, 0);
	triangleScalars->InsertValue(1, 0);
	triangleScalars->InsertValue(2, 1);

	//拓扑结构
	vtkSmartPointer<vtkTriangle> aTriangle = vtkSmartPointer<vtkTriangle>::New();
	aTriangle->GetPointIds()->SetNumberOfIds(3);
	aTriangle->GetPointIds()->SetId(0, 0);
	aTriangle->GetPointIds()->SetId(1, 1);
	aTriangle->GetPointIds()->SetId(2, 2);


	////根据已创建的点来创建线
	//vtkSmartPointer<vtkLine> line0 = vtkSmartPointer<vtkLine>::New();
	//line0->GetPointIds()->SetId(0, 0);
	//line0->GetPointIds()->SetId(1, 1);

	//vtkSmartPointer<vtkLine> line1 = vtkSmartPointer<vtkLine>::New();
	//line1->GetPointIds()->SetId(0, 1);
	//line1->GetPointIds()->SetId(1, 2);

	//vtkSmartPointer<vtkLine> line2 = vtkSmartPointer<vtkLine>::New();
	//line2->GetPointIds()->SetId(0, 2);
	//line2->GetPointIds()->SetId(1, 0);

	////创建单元数组，用于存储以上创建的线段
	//vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
	//lines->InsertNextCell(line0);
	//lines->InsertNextCell(line1);
	//lines->InsertNextCell(line2);


	//将以上三部分组装成一个结构
	vtkSmartPointer<vtkUnstructuredGrid> aTriangleGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
	aTriangleGrid->Allocate(1, 1);
	aTriangleGrid->SetPoints(points);
	aTriangleGrid->GetPointData()->SetScalars(triangleScalars);
	aTriangleGrid->InsertNextCell(aTriangle->GetCellType(), aTriangle->GetPointIds());



	////创建vtkPolyData类型的数据，vtkPolyData派生自vtkPointSet
	////vtkPointSet是vtkDataSet的子类，即vtkPolyData是一种数据集
	//vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

	////将创建的点数据加入到vtkPolyData数据里
	//polydata->SetPoints(points);

	//将vtkPolyData类型的数据写入到一个vtk文件，保存位置是工程当前目录
	vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
	writer->SetFileName("triangle.vtk");
	writer->SetInputData(aTriangleGrid);
	writer->Write();

	return 0;
}